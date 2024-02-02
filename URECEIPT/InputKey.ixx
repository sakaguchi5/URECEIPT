//module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
export module Mod_InputKey;
import std;
import Mod_MyCommon;
export
{
    template <typename T>
    class Input
    {
        // �e���v���[�g���� T �� int �܂��� string �ɕϊ��\�ł��邱�Ƃ��m�F����
        static_assert(std::is_integral<T>::value || std::convertible_to<std::string, T>,
            "�����Ȍ^�ł��B�T�|�[�g����Ă���^: int ����� string�ɕϊ��ł���^");

        template <typename>
        using MaybeMonad = std::expected<T, std::string>;

    public:
        static T getInputWithRetry(const std::string& prompt = "�l����͂��Ă�������: ")
        {
            std::string userInput;

            while (true) {
                std::cout << prompt;
                std::getline(std::cin, userInput);

                // ���͕������Maybe���i�h���g���ĔC�ӂ̌^�ɕϊ�
                MaybeMonad<T> result = convertInput<T>(userInput);

                // �ϊ�������������l��Ԃ�
                if (result) {
                    return result.value();
                }
                // �ϊ������s������G���[���b�Z�[�W��\�����čē���
                else {
                    std::cerr << result.error() << std::endl;
                }
            }
        }

        static T getInputWithRetry_ex(tPredicate<T> checkCondition,
            const std::string& prompt = "�l����͂��Ă�������: ",
            const std::string& conditionerror = "�����𖞂����Ă��܂���/�܂��͔͈͊O�ł��B������x�����Ă��������B"
        )
        {
            std::string userInput;

            while (true) {
                std::cout << prompt;
                std::getline(std::cin, userInput);

                // ���͕������Maybe���i�h���g���ĔC�ӂ̌^�ɕϊ�
                MaybeMonad<T> result = convertInput<T>(userInput);

                // �ϊ����������������������s��
                if (result)
                {
                    //������true�Ȃ�l��Ԃ�
                    if (checkCondition(result.value())) {
                        return result.value();
                    }
                    //������false�Ȃ�G���[���b�Z�[�W��\�����čē���
                    else {
                        std::cerr << conditionerror << std::endl;
                    }

                }
                // �ϊ������s������G���[���b�Z�[�W��\�����čē���
                else {
                    std::cerr << result.error() << std::endl;
                }
            }
        }
        //�P�ɓ��͂������𖞂������ǂ����𔻒肷��֐�
        bool validateInput(tPredicate<T> checkCondition,
            const std::string& prompt = "�l����͂��Ă�������: ")
        {
            std::string userInput;

            while (true) {
                std::cout << prompt;
                std::getline(std::cin, userInput);

                // ���͕������Maybe���i�h���g���ĔC�ӂ̌^�ɕϊ�
                MaybeMonad<T> result = convertInput<T>(userInput);

                // �ϊ�������������^�U�l��Ԃ�
                if (result)
                {
                    return checkCondition(result.value());
                }
                // �ϊ������s������G���[���b�Z�[�W��\�����čē���
                else
                {
                    std::cerr << result.error() << std::endl;
                }
            }

        }

    private:
        //���[�U�[�̓��͂��������s���Ă��邩�𔻒f����w���p�[�֐�
        //char�^�̂ݓ��ꉻ
        template <typename>
        static MaybeMonad<T> convertInput(const std::string& input)
        {
            T result{};
            std::istringstream stream(input);
            stream >> result;

            if (stream.fail() || !stream.eof()) {
                return std::unexpected{ "�����ȓ��͂ł��B�ē��͂��Ă��������B" };
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
                return std::unexpected{ "�����ȓ��͂ł��B�ē��͂��Ă��������B" };
            }
        }


    };



}
