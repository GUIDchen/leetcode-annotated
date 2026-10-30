// 题目：434. 字符串中的单词数（Number of Segments in a String）
// 思路：用 istringstream 的 >> 读取，它会自动跳过任意连续空白并逐个取出非空段，读到的次数就是答案。
// 时间复杂度：O(n)，每个字符只被扫描一次；空间复杂度：O(n)，字符串流内部会复制一份输入。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    int countSegments(string s) {  // 统计 s 中被空白分隔出的非空段（单词）个数
        int ans = 0;  // 计数器：每读到一个段就加 1
        istringstream ss(s);  // 把 s 包装成字符串流，方便按空白切词
        while (ss >> s) ++ans;  // >> 会跳过前导空白再读一段；读成功就 ++ans，读到流尾则循环结束
        return ans;  // 返回统计到的段数
    }
};