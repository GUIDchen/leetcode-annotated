// 3582. 为视频标题生成标签（Generate Tag for Video Caption）
// 核心思路：按空白切分标题，所有单词转小写、除首词外首字母大写，以 '#' 开头拼接后截断到 100 个字符。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为标题字符总数。
class Solution {  // 定义题解类
public:  // 公有接口，判题器从这里调用
    string generateTag(string caption) {  // 把视频标题转换成标签
        istringstream iss(caption);  // 用字符串输入流按空白切分标题
        string word;  // 存放当前读出的单词
        ostringstream oss;  // 用输出流逐段拼装标签
        oss << "#";  // 标签固定以井号开头
        bool first = true;  // 标记当前是否为第一个单词
        while (iss >> word) {  // 依次取出每个单词
            transform(word.begin(), word.end(), word.begin(), ::tolower);  // 整词转小写，统一大小写规则
            if (first) {  // 第一个单词整词小写并直接拼接
                oss << word;  // 拼接首词
                first = false;  // 之后按驼峰规则处理
            } else {  // 非首词需要首字母大写
                word[0] = toupper(word[0]);  // 首字母转大写
                oss << word;  // 拼接转换后的单词
            }  // 结束 if-else 分支
            if (oss.str().length() >= 100) {  // 标签长度达到上限就停止
                break;  // 提前跳出循环
            }  // 结束长度判断
        }  // 结束单词遍历

        string ans = oss.str();  // 取出拼装好的字符串
        if (ans.length() > 100) {  // 超过 100 个字符需要截断
            ans = ans.substr(0, 100);  // 只保留前 100 个字符
        }  // 结束截断分支
        return ans;  // 返回最终标签
    }  // 结束函数
};  // 结束类定义
