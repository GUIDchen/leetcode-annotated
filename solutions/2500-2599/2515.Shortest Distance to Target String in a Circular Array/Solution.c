// 题目：2515. 到目标字符串的最短距离（Shortest Distance to Target String in a Circular Array）
// 思路：枚举所有等于 target 的下标，环形数组上两点的距离是 min(|i-start|, n-|i-start|)，在所有候选中取最小值。
// 时间复杂度：O(n)，只需一遍扫描；空间复杂度：O(1)，只用常数个整型变量。
#define min(a, b) ((a) < (b) ? (a) : (b))  // 宏：返回两者中较小的一个（C 中没有 std::min）

int closestTarget(char** words, int wordsSize, char* target, int startIndex) {  // words 是字符串数组，wordsSize 为长度，startIndex 为起点
    int n = wordsSize;  // 环形数组的长度
    int ans = n;  // 初值取最大可能距离 n，同时充当「尚未找到」的哨兵

    for (int i = 0; i < n; i++) {  // 逐个检查每个位置
        if (strcmp(words[i], target) == 0) {  // 该位置字符串与目标串相同（strcmp 返回 0 表示相等）
            int t = abs(i - startIndex);  // 两个下标之差的绝对值
            int dist = min(t, n - t);  // 环形距离：从另一侧绕过去可能更近，取 n - t
            ans = min(ans, dist);  // 用更小的距离更新答案
        }
    }

    return ans == n ? -1 : ans;  // ans 从未被更新说明目标串不存在，返回 -1；否则返回最短距离
}
