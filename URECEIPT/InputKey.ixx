//module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
export module Mod_InputKey;
import std;
import Mod_MyCommon;
export
{
    template <typename T>
    class Input
    {
        // テンプレート引数 T が int または string に変換可能であることを確認する
        static_assert(std::is_integral<T>::value || std::convertible_to<std::string, T>,
            "無効な型です。サポートされている型: int および stringに変換できる型");

        template <typename>
        using MaybeMonad = std::expected<T, std::string>;

    public:
        static T getInputWithRetry(const std::string& prompt = "値を入力してください: ")
        {
            std::string userInput;

            while (true) {
                std::cout << prompt;
                std::getline(std::cin, userInput);

                // 入力文字列をMaybeモナドを使って任意の型に変換
                MaybeMonad<T> result = convertInput<T>(userInput);

                // 変換が成功したら値を返す
                if (result) {
                    return result.value();
                }
                // 変換が失敗したらエラーメッセージを表示して再入力
                else {
                    std::cerr << result.error() << std::endl;
                }
            }
        }

        static T getInputWithRetry_ex(tPredicate<T> checkCondition,
            const std::string& prompt = "値を入力してください: ",
            const std::string& conditionerror = "条件を満たしていません/または範囲外です。もう一度試してください。"
        )
        {
            std::string userInput;

            while (true) {
                std::cout << prompt;
                std::getline(std::cin, userInput);

                // 入力文字列をMaybeモナドを使って任意の型に変換
                MaybeMonad<T> result = convertInput<T>(userInput);

                // 変換が成功したら条件判定を行う
                if (result)
                {
                    //条件がtrueなら値を返す
                    if (checkCondition(result.value())) {
                        return result.value();
                    }
                    //条件がfalseならエラーメッセージを表示して再入力
                    else {
                        std::cerr << conditionerror << std::endl;
                    }

                }
                // 変換が失敗したらエラーメッセージを表示して再入力
                else {
                    std::cerr << result.error() << std::endl;
                }
            }
        }
        //単に入力が条件を満たすかどうかを判定する関数
        bool validateInput(tPredicate<T> checkCondition,
            const std::string& prompt = "値を入力してください: ")
        {
            std::string userInput;

            while (true) {
                std::cout << prompt;
                std::getline(std::cin, userInput);

                // 入力文字列をMaybeモナドを使って任意の型に変換
                MaybeMonad<T> result = convertInput<T>(userInput);

                // 変換が成功したら真偽値を返す
                if (result)
                {
                    return checkCondition(result.value());
                }
                // 変換が失敗したらエラーメッセージを表示して再入力
                else
                {
                    std::cerr << result.error() << std::endl;
                }
            }

        }

    private:
        //ユーザーの入力が正しく行われているかを判断するヘルパー関数
        //char型のみ特殊化
        template <typename>
        static MaybeMonad<T> convertInput(const std::string& input)
        {
            T result{};
            std::istringstream stream(input);
            stream >> result;

            if (stream.fail() || !stream.eof()) {
                return std::unexpected{ "無効な入力です。再入力してください。" };
            }

            return result;
        }
        template<>
        static MaybeMonad<T> convertInput<char>(const std::string& input)
        {
            if (input.length() == 1) {
                return input[0];
            }
            else {
                return std::unexpected{ "無効な入力です。再入力してください。" };
            }
        }


    };



}
