module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
#include <Windows.h>
#include <Commdlg.h>

export module Mod_FileProcessor;
import std;
import Mod_MyCommon;

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
        /*
        bool GetSelectedFileName(std::string& str) {
            if (GetOpenFileName(&ofn))
            {
                str = szFileName;
                return true;
            }
            else
            {
                std::cout << "ファイルが選択されませんでした。" << std::endl;
                return false;
            }
        }*/

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

        template <class... Args>
        bool processFile(LineParser<Args...> f, Args&... args)
        {
            if (!openFile())
            {
                std::cerr << "ファイルが開けませんでした。\n";
                return false;
            }
            //std::cout << "ファイルが正常に開かれました。\n";
            if (!isFirstLineValid())
            {
                std::cerr << "最初の行が目的のものでない可能性があります。\n";
                closeFile();  // ファイルを閉じる
                return false;
            }
            //std::cout << "最初の行が目的のものであることが確認されました。\n";
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
            return file.is_open();
        }

        bool isFirstLineValid() 
        {
            if (file.is_open()) {
                std::getline(file, firstLine);
                return (firstLine.find(targetString) != std::string::npos);
            }
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
            // キーが存在しない場合は新しいキーと値を追加して true を返す
            fileReaderUmap[key] = MyFileReader(filepath, targetString);
            return true;
        };

        template <class... Args>
        void processFile(const std::string& key,LineParser<Args...> f, Args&... args)
        {
            fileReaderUmap[key].processFile(f, args...);
        };
    private:
        std::unordered_map<std::string, MyFileReader> fileReaderUmap;


        bool writeAnswer(std::deque<Receipt>& ans);
    };



}

module:private;



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

    return false;
}

