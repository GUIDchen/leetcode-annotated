// 题目：3522. 执行指令后的得分（Calculate Score After Performing Instructions）
// 思路：按下标模拟执行，visited 数组防止重复执行造成死循环，遇到 add 加分并后移，遇到 jump 按数值跳转。
// 时间复杂度：O(n)，每个下标最多访问一次；空间复杂度：O(n)，visited 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long calculateScore(vector<string>& instructions, vector<int>& values) {  // instructions：指令表；values：每个下标的数值；返回最终得分
        int n = values.size();  // n：指令与数值的个数
        vector<bool> vis(n, false);  // vis[i] 标记下标 i 是否已经执行过
        long long ans = 0;  // ans：累计得分，用 long long 防止溢出
        int i = 0;  // i：当前执行到的下标，从 0 开始

        while (i >= 0 && i < n && !vis[i]) {  // 下标合法且该指令还没执行过时继续模拟
            vis[i] = true;  // 标记该下标已访问，避免死循环
            if (instructions[i][0] == 'a') {  // 指令首字母是 a，说明是 add
                ans += values[i];  // 加上当前下标的数值
                i += 1;  // 下标后移一位
            } else {  // 否则是 jump 指令
                i += values[i];  // 下标按 values[i] 跳转
            }  // add 分支结束
        }  // 循环结束

        return ans;  // 返回最终得分
    }  // 方法结束
};  // 类结束
