module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
#include <Windows.h>
#include <Commdlg.h>

export module Mod_FileProcessor;
import std;
import Mod_MyCommon;
import Mod_OperationHandler; 

export
{
    class FileSelector {
    public:
        FileSelector() {
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = NULL;
            ofn.lpstrFilter = "テキストファイル\0*.txt\0すべてのファイル\0*.*\0";
            ofn.lpstrFile = szFileName;
            ofn.nMaxFile = MAX_PATH;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
        }

        std::string GetSelectedFileName() {

            if (GetOpenFileName(&ofn))
            {
                return szFileName;
            }
            else
            {
                std::cout << "ファイルが選択されませんでした。" << std::endl;
                return std::string();//空の文字列を返す
            }
        }

    private:
        OPENFILENAME ofn;
        char szFileName[MAX_PATH] = "";

    };

    template <class... Args>
    using LineParser = std::function<void(const std::string& line, Args&... args)>;
    class MyFileReader {
    public:
        MyFileReader(){}
        MyFileReader(const std::string& filepath, const std::string& targetString)
            : filepath(filepath), targetString(targetString) {}

        //最初の行が目的のものでないかどうかのみを判断する関数
        bool FirstLineCheck()
        {
            if (!openFile()){
                return false;
            }
            if (!isFirstLineValid()){
                closeFile();  // ファイルを閉じる
                return false;
            }
            closeFile();  // ファイルを閉じる
            return true;
        }
        //最初の行が目的のものでないかどうかを判断したのち、構文解析を実行する関数
        template <class... Args>
        bool processFile(LineParser<Args...> f, Args&... args)
        {
            if (!openFile()){
                return false;
            }
            if (!isFirstLineValid()){
                closeFile();  // ファイルを閉じる
                return false;
            }
            parseRemainingLines(f, args...);
            closeFile();  // ファイルを閉じる
            return true;
        }

    private:
        std::ifstream file;
        std::string filepath;
        std::string firstLine;
        std::string targetString;
    private:
        bool openFile() 
        {
            file.open(filepath);
            if (file.is_open()){
                return true;
            }
            else{
                std::cerr << "ファイルが開けませんでした。\n";
                return false;
            }
        }

        bool isFirstLineValid() 
        {
            if (file.is_open()) {
                std::getline(file, firstLine);
                return (firstLine.find(targetString) != std::string::npos);
            }
            std::cerr << "最初の行が目的のものでない可能性があります。\n";
            return false;
        }

        template <class... Args>
        bool parseRemainingLines(LineParser<Args...> f, Args&... args)
        {
            if (file.is_open()) 
            {
                std::string line;
                while (std::getline(file, line)) 
                {
                    f(line, args...);
                }
                return true;
            }
            return false;
        }

        void closeFile() 
        {
            file.close();
        }
    };


    class FileProcessor {
    public:
        FileProcessor() {}

        bool addfileReaderUmap(const std::string& key, const std::string& filepath, const std::string& targetString)
        {
            // find を使用してキーの存在を確認
            auto it = fileReaderUmap.find(key);

            // キーが存在する場合は false を返す
            if (it != fileReaderUmap.end()) {
                return false;
            }

            // 指定されたファイルパスとターゲット文字列を使用してMyFileReaderオブジェクトを生成
            // fileReaderObject.FirstLineCheck()でファイルの最初の行を確認し、成功した場合はfileReaderUmapに追加してtrueを返す
            // 失敗した場合はfalseを返す
            if (auto fileReaderObject = MyFileReader(filepath, targetString); fileReaderObject.FirstLineCheck()) {
                // ファイルリーダーを連想配列に追加する
                fileReaderUmap.try_emplace(key, std::move(fileReaderObject));
                return true;
            }
            else {
                // ファイルの最初の行が一致しない場合はfalseを返す
                return false;
            }
            
        };

        template <class... Args>
        void processFile(const std::string& key,LineParser<Args...> f, Args&... args)
        {
            fileReaderUmap[key].processFile(f, args...);
        };

        // ファイルパスを取得して処理する関数
        void processFilePath(const OperationHandler<std::string>& oHandler, const std::string& key, const std::string& targetstring);


        static bool writeAnswer(std::deque<Receipt>& ans);
        static bool writeAnswer(std::deque<Receipt>& ans, const std::string& filepath);
    private:
        std::unordered_map<std::string, MyFileReader> fileReaderUmap;


    };



}

module:private;



void FileProcessor::processFilePath(const OperationHandler<std::string>& oHandler, const std::string& key, const std::string& targetstring)
{
    std::string filepath;
    // 空でない文字列が入力されるまでループ
    while (true)
    {
        // oHandlerの要素数が2でなければならない
        filepath = oHandler.selectOperation("1でデフォルト、2でファイル選択: ");
        //短絡評価を利用した条件分岐
        //空でない文字列が入力され、かつファイルの最初の行を確認して成功した場合ループを抜ける
        if (!filepath.empty() && addfileReaderUmap(key, filepath, targetstring))
            break;
        std::cout << "もう一度選択し直してください" << std::endl;
    }
}

bool FileProcessor::writeAnswer(std::deque<Receipt>& ans)
{
    std::map<int, std::vector<int>> result;
    for (const auto& receipt : ans) {
        result[receipt.date].push_back(receipt.price);
    }

    for (const auto& entry : result) {
        std::cout << "Key: " << entry.first << ", Values: ";
        for (int value : entry.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    std::ofstream outputFile("output.txt"); // 出力ファイル名を適切なものに変更

    for (const auto& entry : result) {
        outputFile << entry.first << " ";
        for (int value : entry.second) {
            outputFile << value << " ";
        }
        outputFile << std::endl;
    }
    std::cout << "正常に出力されました" << std::endl;

    return true;
}

bool FileProcessor::writeAnswer(std::deque<Receipt>& ans, const std::string& filepath)
{
    std::map<int, std::vector<int>> result;
    for (const auto& receipt : ans) {
        result[receipt.date].push_back(receipt.price);
    }

    for (const auto& entry : result) {
        std::cout << "Key: " << entry.first << ", Values: ";
        for (int value : entry.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    std::ofstream outputFile(filepath); // 出力ファイル名を適切なものに変更

    for (const auto& entry : result) {
        outputFile << entry.first << " ";
        for (int value : entry.second) {
            outputFile << value << " ";
        }
        outputFile << std::endl;
    }
    std::cout << "正常に出力されました" << std::endl;
    return true;
}