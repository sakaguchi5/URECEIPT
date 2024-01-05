module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
export module Mod_DPProcessor;
import std;
import Mod_MyCommon;

export
{
    class DynamicProgrammingProcessor {
    public:
        DynamicProgrammingProcessor() {}

        void initializeDP(Config& config, const std::vector<Receipt>& receipts);
        void calculateDP(Config& config, const std::vector<Receipt>& receipts);

        std::vector<std::vector<int>> dp;
    private:
        /*
        Config& config;
        const std::vector<Receipt>& receipts;*/
        // 他のプライベートメンバやDP計算ロジックをここに追加
    };

    class CombinationSearch {
    public:
        CombinationSearch() {}
        /*
        CombinationSearch(Config& config, const std::vector<Receipt>& receipts)
            : receipts(receipts), config(config) {}*/

        void searchCombination(Config& config, const std::vector<Receipt>& receipts, const std::vector<std::vector<int>>& dp, int i, int j);


        std::vector<std::deque<Receipt>> GetAnswer() { return ans; }

    private:
        //const std::vector<Receipt>& receipts;
        // 他のプライベートメンバや探索ロジックをここに追加
        //Config& config;
        std::deque<Receipt> keiro;
        std::vector<std::deque<Receipt>> ans;
        int count = 0;

        void searchCombinations(Config& config, const std::vector<Receipt>& receipts,const std::vector<std::vector<int>>& dp, int i, int j);

    };



}


module:private;

void DynamicProgrammingProcessor::initializeDP(Config& config, const std::vector<Receipt>& receipts)
{
    auto N = receipts.size();
    auto MAX = config.MAX;
    dp.clear();
    dp.resize(N + 1, std::vector<int>(MAX + 1));
    dp[0][0] = 1;

}

void DynamicProgrammingProcessor::calculateDP(Config& config, const std::vector<Receipt>& receipts)
{
    auto N = receipts.size();
    auto MAX = config.MAX;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < MAX; ++j) {
            dp[i + 1][j] += dp[i][j];
            if (j + receipts[i].price < MAX)
                dp[i + 1][j + receipts[i].price] += dp[i][j];
        }
    }
}

void CombinationSearch::searchCombination(Config& config, const std::vector<Receipt>& receipts, const std::vector<std::vector<int>>& dp, int i, int j)
{
    ans.clear();
    searchCombinations(config, receipts, dp, i, j);
}

void CombinationSearch::searchCombinations(Config& config, const std::vector<Receipt>& receipts,const std::vector<std::vector<int>>& dp, int i, int j)
{
    if (count > config.maxCountThreshold || ans.size() >= config.maxSizeThreshold)
    {
        return;
    }
    if (i == 0)
    {
        if (j == 0)
        {
            if (config.minCount <= count && count <= config.maxCount)
            {
                ans.push_back(keiro);
            }

        }
        return;
    }

    if (dp[i - 1][j])
    {
        searchCombinations(config, receipts,dp, i - 1, j);
    }
    if (j - receipts[i - 1].price >= 0 && dp[i - 1][j - receipts[i - 1].price])
    {
        keiro.push_front(receipts[i - 1]);
        count++;
        searchCombinations(config, receipts, dp, i - 1, j - receipts[i - 1].price);
        keiro.pop_front();
        count--;
    }

}