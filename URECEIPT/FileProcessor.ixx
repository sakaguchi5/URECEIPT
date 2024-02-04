module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
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

        //�ŏ��̍s���ړI�̂��̂łȂ����ǂ����݂̂𔻒f����֐�
        bool FirstLineCheck()
        {
            if (!openFile()){
                return false;
            }
            if (!isFirstLineValid()){
                closeFile();  // �t�@�C�������
                return false;
            }
            closeFile();  // �t�@�C�������
            return true;
        }
        //�ŏ��̍s���ړI�̂��̂łȂ����ǂ����𔻒f�����̂��A�\����͂����s����֐�
        template <class... Args>
        bool processFile(LineParser<Args...> f, Args&... args)
        {
            if (!openFile()){
                return false;
            }
            if (!isFirstLineValid()){
                closeFile();  // �t�@�C�������
                return false;
            }
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
            if (file.is_open()){
                return true;
            }
            else{
                std::cerr << "�t�@�C�����J���܂���ł����B\n";
                return false;
            }
        }

        bool isFirstLineValid() 
        {
            if (file.is_open()) {
                std::getline(file, firstLine);
                return (firstLine.find(targetString) != std::string::npos);
            }
            std::cerr << "�ŏ��̍s���ړI�̂��̂łȂ��\��������܂��B\n";
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

            // �w�肳�ꂽ�t�@�C���p�X�ƃ^�[�Q�b�g��������g�p����MyFileReader�I�u�W�F�N�g�𐶐�
            // fileReaderObject.FirstLineCheck()�Ńt�@�C���̍ŏ��̍s���m�F���A���������ꍇ��fileReaderUmap�ɒǉ�����true��Ԃ�
            // ���s�����ꍇ��false��Ԃ�
            if (auto fileReaderObject = MyFileReader(filepath, targetString); fileReaderObject.FirstLineCheck()) {
                // �t�@�C�����[�_�[��A�z�z��ɒǉ�����
                fileReaderUmap.try_emplace(key, std::move(fileReaderObject));
                return true;
            }
            else {
                // �t�@�C���̍ŏ��̍s����v���Ȃ��ꍇ��false��Ԃ�
                return false;
            }
            
        };

        template <class... Args>
        void processFile(const std::string& key,LineParser<Args...> f, Args&... args)
        {
            fileReaderUmap[key].processFile(f, args...);
        };

        // �t�@�C���p�X���擾���ď�������֐�
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
    // ��łȂ������񂪓��͂����܂Ń��[�v
    while (true)
    {
        // oHandler�̗v�f����2�łȂ���΂Ȃ�Ȃ�
        filepath = oHandler.selectOperation("1�Ńf�t�H���g�A2�Ńt�@�C���I��: ");
        //�Z���]���𗘗p������������
        //��łȂ������񂪓��͂���A���t�@�C���̍ŏ��̍s���m�F���Đ��������ꍇ���[�v�𔲂���
        if (!filepath.empty() && addfileReaderUmap(key, filepath, targetstring))
            break;
        std::cout << "������x�I���������Ă�������" << std::endl;
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

    std::ofstream outputFile("output.txt"); // �o�̓t�@�C������K�؂Ȃ��̂ɕύX

    for (const auto& entry : result) {
        outputFile << entry.first << " ";
        for (int value : entry.second) {
            outputFile << value << " ";
        }
        outputFile << std::endl;
    }
    std::cout << "����ɏo�͂���܂���" << std::endl;

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

    std::ofstream outputFile(filepath); // �o�̓t�@�C������K�؂Ȃ��̂ɕύX

    for (const auto& entry : result) {
        outputFile << entry.first << " ";
        for (int value : entry.second) {
            outputFile << value << " ";
        }
        outputFile << std::endl;
    }
    std::cout << "����ɏo�͂���܂���" << std::endl;
    return true;
}