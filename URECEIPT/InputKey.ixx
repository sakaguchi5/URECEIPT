//module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
export module Mod_InputKey;
import std;
import Mod_MyCommon;
export
{
    template <typename T>
    class Input {
    public:
        // �e���v���[�g���� T �� int �܂��� string �ɕϊ��\�ł��邱�Ƃ��m�F����
        static T read(const std::string& prompt = "�l����͂��Ă�������: ") {

            static_assert(std::is_integral<T>::value || std::convertible_to<std::string, T>,
                "�����Ȍ^���͂ł��B�T�|�[�g����Ă���^: int ����� string�ɕϊ��ł���^");

            T value;
            while (true) {
                std::cout << prompt;
                // ���͂��L�����ǂ������m�F
                if (getValidInput(value)) {
                    return value;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

    private:
        // ���͂��L�����ǂ������m�F���邽�߂̃w���p�[�֐�
        template <typename T>
        static bool getValidInput(T& value) {
            if (std::cin >> value) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
            std::cerr << "�����ȓ��͂ł��B�ē��͂��Ă��������B" << std::endl;
            return false;
        }
    };

    // int�^�ɓ��ꉻ���ꂽ�N���X�e���v���[�g
    class InputInt : public Input<int> {
    public:
        // ����̏����𖞂��������̓��͂��󂯕t����
        static int readex(const std::string& prompt = "�l����͂��Ă�������: ", IntPredicate checkCondition = [](int) { return true; }) {
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
        // ����̏����𖞂��������̓��͂��L�����ǂ������m�F���邽�߂̃w���p�[�֐�
        static bool getValidIntPredicateInput(int& value, IntPredicate checkCondition) {
            if (std::cin >> value) {
                if (checkCondition(value)) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return true;
                }
                else {
                    std::cerr << "�����𖞂����Ă��܂���/�܂��͔͈͊O�ł��B������x�����Ă��������B" << std::endl;
                    return false;
                }

            }
            std::cerr << "�����ȓ��͂ł��B�ē��͂��Ă��������B" << std::endl;
            return false;
        }
    };



}
