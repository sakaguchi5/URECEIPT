
module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
export module Mod_OperationHandler;
import std;
import Mod_MyCommon;
import Mod_InputKey;

export
{
    template <class FuncReturn>
    class OperationHandler
    {
        using FunctionType = std::function<FuncReturn()>;
    public:
        OperationHandler() {}

        ~OperationHandler() {}


        // 操作を追加する
        void addFunction(const FunctionType& f)
        {
            operationList.push_back(f);
        }
        // 操作を全削除する
        void removeAllFunctions()
        {
            operationList.clear();
        }

        //1からoperationListのサイズまでの中から操作を選択する
        FuncReturn selectOperation(const std::string& prompt = "") const
        {
            std::cout << "1から" << operationList.size() << "の中から選んでください" << std::endl;
            std::cout << prompt;
            return inputGet();

            //1からxの中から選んでください　　　
        }
    private:
        std::vector<FunctionType> operationList;

        // 指定された順序の操作を実行する
        FuncReturn Get(int order) const
        {
            return operationList[order]();
        }

        // 操作を選択して実行するための入力を受け付ける
        FuncReturn inputGet() const
        {
            // 入力が特定の範囲にあるかどうかを確認する条件
            IntPredicate isInRange = [*this](int x)
                {
                    if (0 < x && x < operationList.size() + 1)
                    {
                        return true;
                    }
                    return false;
                };
            auto num = InputInt::readex("整数値を入力してください: ", isInRange);
            std::cout << num << std::endl;
            return Get(num - 1);
        }

    };



}