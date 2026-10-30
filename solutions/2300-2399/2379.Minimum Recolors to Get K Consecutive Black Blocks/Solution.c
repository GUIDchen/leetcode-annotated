// 题目：2379. 得到 K 个黑块的最少涂色次数（Minimum Recolors to Get K Consecutive Black Blocks）
// 思路：定长滑窗。任意长度为 k 的窗口内，把其中的 'W' 全涂成 'B' 即可得到连续 k 个黑块，涂色次数等于窗口内 'W' 的个数，因此答案为所有窗口中 'W' 数的最小值；用窗口内 'B' 的数量做维护更省事。
// 时间复杂度：O(n)，窗口整体右移一次即可；空间复杂度：O(1)，只用了若干计数变量。
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 判题片段不允许新增 #include，这里用宏自行实现取较小值

int minimumRecolors(char* blocks, int k) {  // blocks 为 'B'/'W' 组成的字符串，k 为需要的连续黑块长度
    int n = strlen(blocks);  // 取字符串长度，作为滑窗右端上界
    int count = 0;  // count 记录当前窗口内 'B' 的个数
    for (int i = 0; i < k; i++) {  // 先统计第一个窗口 [0, k) 内的黑块数
        count += blocks[i] == 'B';  // (blocks[i] == 'B') 结果为 0/1，直接累加即可统计黑块
    }  // 首个窗口统计完毕
    int ans = k - count;  // 把窗口内 'W' 全部涂黑需要 k - count 次，先作为当前最优答案
    for (int i = k; i < n; i++) {  // 窗口每次右移一格，i 是窗口右端（新进入窗口的下标）
        count -= blocks[i - k] == 'B';  // 移出左端元素：若它是 'B'，黑块计数减一
        count += blocks[i] == 'B';  // 移入右端元素：若它是 'B'，黑块计数加一
        ans = min(ans, k - count);  // 用当前窗口的涂色次数更新最小值
    }  // 滑窗遍历结束
    return ans;  // 返回所有长度为 k 的窗口中最少的涂色次数
}  // 函数结束