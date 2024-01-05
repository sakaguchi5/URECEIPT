//module; // グローバルモジュールフラグメント
// #includeはグローバルモジュールフラグメント内で行う
export module Mod_InputKey;
import std;
import Mod_MyCommon;
export
{
    template <typename T>
    class Input {
    public:
        // テンプレート引数 T が int または string に変換可能であることを確認する
        static T read(const std::string& prompt = "値を入力してください: ") {

            static_assert(std::is_integral<T>::value || std::convertible_to<std::string, T>,
                "無効な型入力です。サポートされている型: int および stringに変換できる型");

            T value;
            while (true) {
                std::cout << prompt;
                // 入力が有効かどうかを確認
                if (getValidInput(value)) {
                    return value;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    private:
        // 入力が有効かどうかを確認するためのヘルパー関数
        template <typename T>
        static bool getValidInput(T& value) {
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
            std::cerr << "無効な入力です。再入力してください。" << std::endl;
            return false;
        }
    };

    // int型に特殊化されたクラステンプレート
    class InputInt : public Input<int> {
    public:
        // 特定の条件を満たす整数の入力を受け付ける
        static int readex(const std::string& prompt = "値を入力してください: ", IntPredicate checkCondition = [](int) { return true; }) {
            int value;
            while (true) {
                std::cout << prompt;

                if (getValidIntPredicateInput(value, checkCondition)) {
                    return value;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    private:
        // 特定の条件を満たす整数の入力が有効かどうかを確認するためのヘルパー関数
        static bool getValidIntPredicateInput(int& value, IntPredicate checkCondition) {
            if (std::cin >> value) {
                if (checkCondition(value)) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return true;
                }
                else {
                    std::cerr << "条件を満たしていません/または範囲外です。もう一度試してください。" << std::endl;
                    return false;
                }

            }
            std::cerr << "無効な入力です。再入力してください。" << std::endl;
            return false;
        }
    };



}
