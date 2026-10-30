// 题目：3921. 分数验证器（Score Validator）
// 思路：按题意从左到右模拟：数字事件把数值加进总分，"W" 只累加计数器并在到达 10 时立即停止，其余事件（WD/NB）各加 1 分。
// 时间复杂度：O(n)，每个事件只处理一次；空间复杂度：O(1)，只用 score 与 counter 两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> scoreValidator(vector<string>& events) {  // events：事件数组，返回 [总分, 计数器]
        int score = 0;  // 总分初始为 0
        int counter = 0;  // 计数器（"W" 的个数）初始为 0
        for (string event : events) {  // 从左到右依次处理每个事件
            if (isdigit(event[0])) {  // 首字符是数字，说明这是可加分的事件
                score += stoi(event);  // 把整个事件转成整数累加进总分
            } else if (event == "W") {  // 三振事件：只增加计数器，不加分
                if (++counter == 10) {  // 先自增再判断，计数器到 10 就结束处理
                    break;  // 达到 10，立刻停止处理后面的事件
                }  // 没到 10 就继续下一个事件
            } else {  // 剩下的是 "WD"、"NB" 这类事件
                score++;  // 这类事件各加 1 分
            }  // 事件分支结束
        }  // 遍历结束
        return {score, counter};  // 按题目要求返回总分与计数器
    }  // 方法结束
};  // 类定义结束
