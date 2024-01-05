
module; // �O���[�o�����W���[���t���O�����g
// #include�̓O���[�o�����W���[���t���O�����g���ōs��
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


        // �����ǉ�����
        void addFunction(const FunctionType& f)
        {
            operationList.push_back(f);
        }
        // �����S�폜����
        void removeAllFunctions()
        {
            operationList.clear();
        }

        //1����operationList�̃T�C�Y�܂ł̒����瑀���I������
        FuncReturn selectOperation(const std::string& prompt = "") const
        {
            std::cout << "1����" << operationList.size() << "�̒�����I��ł�������" << std::endl;
            std::cout << prompt;
            return inputGet();

            //1����x�̒�����I��ł��������@�@�@
        }
    private:
        std::vector<FunctionType> operationList;

        // �w�肳�ꂽ�����̑�������s����
        FuncReturn Get(int order) const
        {
            return operationList[order]();
        }

        // �����I�����Ď��s���邽�߂̓��͂��󂯕t����
        FuncReturn inputGet() const
        {
            // ���͂�����͈̔͂ɂ��邩�ǂ������m�F�������
            IntPredicate isInRange = [*this](int x)
                {
                    if (0 < x && x < operationList.size() + 1)
                    {
                        return true;
                    }
                    return false;
                };
            auto num = InputInt::readex("�����l����͂��Ă�������: ", isInRange);
            std::cout << num << std::endl;
            return Get(num - 1);
        }

    };



}