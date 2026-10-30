// 题目：1832. 判断句子是否为全字母句（Check if the Sentence Is Pangram）
// 思路：用长度 26 的标记数组记录出现过的字母，最后检查 26 个字母是否全部出现过。
// 时间复杂度：O(n)，n 为句子长度；空间复杂度：O(1)，固定 26 个标记。
bool checkIfPangram(char* sentence) {  // sentence：只含小写字母的句子；返回它是否为全字母句
    int vis[26] = {0};  // vis：标记数组，vis[i] = 1 表示第 i 个字母出现过
    for (int i = 0; sentence[i]; i++) {  // 遍历句子，遇到字符串结束符即停止
        vis[sentence[i] - 'a'] = 1;  // 字母减去 'a' 得到 0..25 的下标并打上标记
    }  // 遍历结束
    for (int i = 0; i < 26; i++) {  // 检查 26 个小写字母是否都出现过
        if (!vis[i]) {  // 有字母一次都没出现
            return 0;  // 不是全字母句，返回 false（0）
        }  // 分支结束
    }  // 检查结束
    return 1;  // 全部出现，返回 true（1）
}  // 函数结束