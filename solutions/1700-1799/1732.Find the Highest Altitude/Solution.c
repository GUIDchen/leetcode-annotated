// 题目：1732. 找到最高海拔（Find the Highest Altitude）
// 思路：从海拔 0 出发依次累加相邻高差，边累加边记录出现过的最大值。
// 时间复杂度：O(n)，只扫一遍高差数组；空间复杂度：O(1)，只用两个整型变量。
#define max(a, b) (((a) > (b)) ? (a) : (b))  // 宏定义取较大值，判题器不需要额外的 max 头文件

int largestAltitude(int* gain, int gainSize) {  // gain 是相邻两点的海拔差数组，gainSize 是它的长度
    int ans = 0;  // 记录出现过的最高海拔，起点海拔按题意取 0
    int h = 0;  // 当前海拔，从起点的 0 开始
    for (int i = 0; i < gainSize; i++) {  // 依次走过每一段路程
        h += gain[i];  // 累加本段高差，得到当前点的海拔
        ans = max(ans, h);  // 用当前海拔更新历史最高海拔
    }  // 遍历结束
    return ans;  // 返回最高海拔
}  // 函数结束