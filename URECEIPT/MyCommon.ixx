module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う

export module Mod_MyCommon;
import std;
export
{

	using vi = std::vector<int>;//intのvector
    using IntPredicate = std::function<bool(int)>;//整数述語の型
    
    constexpr std::string_view TARGETDATASTRING = "TakaishiURECEIPT";
    constexpr std::string_view TARGETCONFIGSTRING = "TakaishiURECEIPT";


	//各スマートポイントのエイリアステンプレート
	template <class T>
	using u_p = std::unique_ptr<T>;
	template <class T>
	using s_p = std::shared_ptr<T>;
	template <class T>
	using w_p = std::weak_ptr<T>;
    //レシート
    struct Receipt {
    public:
        Receipt() { date = 0; price = 0; }
        Receipt(int date, int price) : date(date), price(price) {}

        int date;//年月日
        int price;//金額
    };
    //設定
    struct Config
    {
    public:
        int maxCountThreshold = 0;
        int maxSizeThreshold = 0;
        int minCount = 0;
        int maxCount = 0;
        int MAX = 0;
        int target = 0;/*const*/

        // 設定情報を表示するメソッド
        void PrintConfig();
            /*
        {
            std::cout << "maxCountThreshold: " << maxCountThreshold << std::endl;
            std::cout << "maxSizeThreshold: " << maxSizeThreshold << std::endl;
            std::cout << "minCount: " << minCount << std::endl;
            std::cout << "maxCount: " << maxCount << std::endl;
            std::cout << "MAX: " << MAX << std::endl;
            std::cout << "target: " << target << std::endl;
        };*/
        //自動的にinline宣言されてしまうため外部リンケージを持たない?
        
    };

    class MyData
    {
    public:
        MyData()
        {
            //config.PrintConfig();
        }

        ~MyData()
        {
        }
        

        // 商品リストを初期化
        std::vector<Receipt> receipts;
        Config config;
    private:


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

void Config::PrintConfig()
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
