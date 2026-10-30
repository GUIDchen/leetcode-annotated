// 题目：1629. 按键持续时间最长的键（Slowest Key）
// 思路：相邻两次释放时刻之差就是该键的持续时间，顺序扫描一遍取最大；时长相同则取字符更大（字典序更靠后）的键。
// 时间复杂度：O(n)，只扫描一次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {  // releaseTimes 为每个键的释放时刻，keysPressed 为按键序列
        char ans = keysPressed[0];  // 第 0 个键的持续时间就是 releaseTimes[0]，先把它当作当前最优
        int mx = releaseTimes[0];  // 记录当前最长的持续时间
        for (int i = 1, n = releaseTimes.size(); i < n; ++i) {  // 从第 1 个键开始扫描，同时缓存长度 n 避免重复调用 size()
            int d = releaseTimes[i] - releaseTimes[i - 1];  // 当前按键的持续时间 = 本次释放时刻 - 上次释放时刻
            if (d > mx || (d == mx && keysPressed[i] > ans)) {  // 持续时间更长，或时长相同但字符更大（题目要求同长取较大字符）时更新
                mx = d;  // 更新最长持续时间
                ans = keysPressed[i];  // 更新答案字符
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回持续时间最长（同长取更大字符）的键
    }  // 方法结束
};  // 类定义结束