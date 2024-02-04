module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
export module Mod_MyCommon;
import std;
export
{

	using vi = std::vector<int>;//int��vector
    template <typename T>
    using tPredicate = std::function<bool(const T&)>;// ����������s���֐��^t

    using IntPredicate = tPredicate<int>;//int�^�̈��������q��̌^

    constexpr std::string_view TARGETDATASTRING = "TakaishiURECEIPT";
    constexpr std::string_view TARGETCONFIGSTRING = "TakaishiURECEIPT";

    
    // �������Ώۂ̕����Ɠ��������ǂ������m�F�����^�e���v���[�g�֐�
    template <char TargetChar>
    bool isTargetChar(char c) { return (c == TargetChar); }

	//�e�X�}�[�g�|�C���g�̃G�C���A�X�e���v���[�g
	template <class T>
	using u_p = std::unique_ptr<T>;
	template <class T>
	using s_p = std::shared_ptr<T>;
	template <class T>
	using w_p = std::weak_ptr<T>;
    //���V�[�g
    struct Receipt {
    public:
        Receipt() { date = 0; price = 0; }
        Receipt(int date, int price) : date(date), price(price) {}

        int date;//�N����
        int price;//���z
    };
    //�ݒ�
    struct Config
    {
    public:
        int maxCountThreshold = 0;
        int maxSizeThreshold = 0;
        int minCount = 0;
        int maxCount = 0;
        int MAX = 0;
        int target = 0;/*const*/

        // �ݒ����\�����郁�\�b�h
        void PrintConfig() const;
            /*
        {
            std::cout << "maxCountThreshold: " << maxCountThreshold << std::endl;
            std::cout << "maxSizeThreshold: " << maxSizeThreshold << std::endl;
            std::cout << "minCount: " << minCount << std::endl;
            std::cout << "maxCount: " << maxCount << std::endl;
            std::cout << "MAX: " << MAX << std::endl;
            std::cout << "target: " << target << std::endl;
        };*/
        //�����I��inline�錾����Ă��܂����ߊO�������P�[�W�������Ȃ�?
        
    };

    struct MyData
    {
        //���V�[�g
        std::vector<Receipt> receipts;
        //�ݒ�
        Config config;
    };

    void displayResults(std::vector<std::deque<Receipt>>& ans);

    class ResultDisplay {
    public:
        ResultDisplay() {}

        static void displayResults(std::vector<std::deque<Receipt>>& ans);
    private:
    };
    
}

module:private;

void Config::PrintConfig() const
{
    std::cout << "maxCountThreshold: " << maxCountThreshold << std::endl;
    std::cout << "maxSizeThreshold: " << maxSizeThreshold << std::endl;
    std::cout << "minCount: " << minCount << std::endl;
    std::cout << "maxCount: " << maxCount << std::endl;
    std::cout << "MAX: " << MAX << std::endl;
    std::cout << "target: " << target << std::endl;
}

void displayResults(std::vector<std::deque<Receipt>>& ans)
{
    std::map<int, std::vector<int>> result;
    int casenum = 1;
    for (const auto& receipts : ans) {
        std::cout << "case: " << casenum << std::endl;
        std::cout << "Count" << receipts.size() << std::endl;

        for (const auto& receipt : receipts) {
            result[receipt.date].push_back(receipt.price);
        }

        for (const auto& entry : result) {
            std::cout << "Key: " << entry.first << ", Values: ";
            for (int value : entry.second) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        casenum++;
        result.clear();
    }
}

void ResultDisplay::displayResults(std::vector<std::deque<Receipt>>& ans)
{
    std::map<int, std::vector<int>> result;
    int casenum = 1;
    for (const auto& receipts : ans) {
        std::cout << "case: " << casenum << std::endl;
        std::cout << "Count" << receipts.size() << std::endl;

        for (const auto& receipt : receipts) {
            result[receipt.date].push_back(receipt.price);
        }

        for (const auto& entry : result) {
            std::cout << "Key: " << entry.first << ", Values: ";
            for (int value : entry.second) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        casenum++;
        result.clear();
    }
}