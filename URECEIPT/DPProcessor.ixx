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

        void initializeDP(MyData myData);
        void calculateDP(MyData myData);

        std::vector<std::vector<int>> dp;
    private:
        // 他のプライベートメンバやDP計算ロジックをここに追加
    };

    class CombinationSearch {
    public:
        CombinationSearch() {}

        void searchCombination(MyData myData, const std::vector<std::vector<int>>& dp, int i, int j);


        std::vector<std::deque<Receipt>> GetAnswer() { return ans; }

    private:
        // 他のプライベートメンバや探索ロジックをここに追加
        std::deque<Receipt> keiro;
        std::vector<std::deque<Receipt>> ans;
        int count = 0;

        void searchCombinations(MyData myData,const std::vector<std::vector<int>>& dp, int i, int j);

    };



}


module:private;

void DynamicProgrammingProcessor::initializeDP(MyData myData)
{
    auto N = myData.receipts.size();
    auto MAX = myData.config.MAX;
    dp.clear();
    dp.resize(N + 1, std::vector<int>(MAX + 1));
    dp[0][0] = 1;

}

void DynamicProgrammingProcessor::calculateDP(MyData myData)
{
    auto N = myData.receipts.size();
    auto MAX = myData.config.MAX;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < MAX; ++j) {
            dp[i + 1][j] += dp[i][j];
            if (j + myData.receipts[i].price < MAX)
                dp[i + 1][j + myData.receipts[i].price] += dp[i][j];
        }
    }
}

void CombinationSearch::searchCombination(MyData myData, const std::vector<std::vector<int>>& dp, int i, int j)
{
    ans.clear();
    searchCombinations(myData, dp, i, j);
}

void CombinationSearch::searchCombinations(MyData myData,const std::vector<std::vector<int>>& dp, int i, int j)
{
    if (count > myData.config.maxCountThreshold || ans.size() >= myData.config.maxSizeThreshold)
    {
        return;
    }
    if (i == 0)
    {
        if (j == 0)
        {
            if (myData.config.minCount <= count && count <= myData.config.maxCount)
            {
                ans.push_back(keiro);
            }

        }
        return;
    }

    if (dp[i - 1][j])
    {
        searchCombinations(myData,dp, i - 1, j);
    }
    if (j - myData.receipts[i - 1].price >= 0 && dp[i - 1][j - myData.receipts[i - 1].price])
    {
        keiro.push_front(myData.receipts[i - 1]);
        count++;
        searchCombinations(myData, dp, i - 1, j - myData.receipts[i - 1].price);
        keiro.pop_front();
        count--;
    }

}