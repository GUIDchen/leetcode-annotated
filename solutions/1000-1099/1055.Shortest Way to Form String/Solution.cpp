// 题目：1055. 形成字符串的最短路径（Shortest Way to Form String）
// 思路：每轮用一整份 source 从下标 0 开始贪心匹配 target，记录 target 推进到的位置；若一整份都没匹配上任何字符则无解。
// 时间复杂度：O(m × n)，最坏每轮扫完 source；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shortestWay(string source, string target) {  // source：可重复拼接的原串；target：目标串
        int m = source.size(), n = target.size();  // m、n 分别是两个串的长度
        int ans = 0, j = 0;  // ans 记录用了几份 source，j 是 target 中已匹配到的位置
        while (j < n) {  // 只要 target 还没拼完就继续
            int i = 0;  // 每用一份新的 source 都从它的头部开始扫
            bool ok = false;  // 记录这一份 source 是否匹配到了 target 中的字符
            while (i < m && j < n) {  // 在这份 source 内从左到右贪心匹配
                if (source[i] == target[j]) {  // 字符相等，就可以消耗掉 target 的这个字符
                    ok = true;  // 标记本轮有进展
                    ++j;  // 指向 target 的下一个待匹配字符
                }  // 匹配分支结束
                ++i;  // 无论是否匹配，source 指针都向后移动
            }  // 一份 source 扫描完毕
            if (!ok) {  // 整份 source 都没匹配到任何字符，说明 target 含有 source 中不存在的字符
                return -1;  // 无法拼出 target，返回 -1
            }  // 失败分支结束
            ++ans;  // 成功用掉一份 source，答案加一
        }  // target 全部匹配完成
        return ans;  // 返回所需 source 的最少份数
    }  // 方法结束
};  // 类定义结束