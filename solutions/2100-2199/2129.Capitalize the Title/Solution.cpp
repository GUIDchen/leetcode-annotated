// 题目：2129. 将标题首字母大写（Capitalize the Title）
// 核心思路：先把整个标题转小写，再按空格切词：长度 > 2 的词首字母转大写，其余保持全小写，最后用空格重拼。
// 时间复杂度：O(n)，每个字符只处理常数次；空间复杂度：O(n)，结果字符串与字符串流。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string capitalizeTitle(string title) {  // title：待格式化的标题；返回按规则重排大小写后的标题
        transform(title.begin(), title.end(), title.begin(), ::tolower);  // 先把整段标题原地转成小写，短词要求全小写、长词稍后只改首字母
        istringstream ss(title);  // 用字符串流按空白把单词切出来，空白（含多个空格）会被自动跳过
        string ans;  // ans 存放重新拼接后的结果
        while (ss >> title) {  // 每次 >> 取出一个单词；这里复用 title 变量作为单词缓冲区
            if (title.size() > 2) {  // 只有长度大于 2 的单词才需要把首字母大写
                title[0] = toupper(title[0]);  // 首字母转大写，其余字符此前已经被转成小写
            }
            ans += title;  // 把这个单词追加到结果末尾
            ans += " ";  // 追加分隔用的空格
        }
        ans.pop_back();  // 上面每次都会多加一个空格，末尾多出一个，删掉避免尾部空白
        return ans;  // 返回格式化完成的标题
    }
};