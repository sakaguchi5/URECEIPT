module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
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
            ofn.lpstrFilter = "�e�L�X�g�t�@�C��\0*.txt\0���ׂẴt�@�C��\0*.*\0";
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
                std::cout << "�t�@�C�����I������܂���ł����B" << std::endl;
                return std::string();//��̕������Ԃ�
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
                std::cout << "�t�@�C�����I������܂���ł����B" << std::endl;
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
                std::cerr << "�t�@�C�����J���܂���ł����B\n";
                return false;
            }
            //std::cout << "�t�@�C��������ɊJ����܂����B\n";
            if (!isFirstLineValid())
            {
                std::cerr << "�ŏ��̍s���ړI�̂��̂łȂ��\��������܂��B\n";
                closeFile();  // �t�@�C�������
                return false;
            }
            //std::cout << "�ŏ��̍s���ړI�̂��̂ł��邱�Ƃ��m�F����܂����B\n";
            parseRemainingLines(f, args...);
            closeFile();  // �t�@�C�������
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
            // find ���g�p���ăL�[�̑��݂��m�F
            auto it = fileReaderUmap.find(key);

            // �L�[�����݂���ꍇ�� false ��Ԃ�
            if (it != fileReaderUmap.end()) {
                return false;
            }
            // �L�[�����݂��Ȃ��ꍇ�͐V�����L�[�ƒl��ǉ����� true ��Ԃ�
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

    std::ofstream outputFile("output.txt"); // �o�̓t�@�C������K�؂Ȃ��̂ɕύX

    for (const auto& entry : result) {
        outputFile << entry.first << " ";
        for (int value : entry.second) {
            outputFile << value << " ";
        }
        outputFile << std::endl;
    }

    return false;
}

