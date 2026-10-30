// 题目：682. 棒球比赛（Baseball Game）
// 思路：用一个栈按顺序记录每一轮的有效得分："+" 取前两轮之和、"D" 取上一轮的两倍、"C" 撤销上一轮，最后把栈内得分求和。
// 时间复杂度：O(n)，每条记录只处理一次；空间复杂度：O(n)，栈最多保存 n 个有效得分。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法入口
    int calPoints(vector<string>& operations) {  // operations：按顺序给出的操作记录
        vector<int> stk;  // 用向量模拟栈，只保存当前仍然有效的各轮得分
        for (auto& op : operations) {  // 逐条处理操作；用引用避免字符串拷贝
            int n = stk.size();  // 处理本条操作之前的栈大小
            if (op == "+") {  // 新得分等于前两轮得分之和
                stk.push_back(stk[n - 1] + stk[n - 2]);  // 取栈顶两个有效得分相加后入栈
            } else if (op == "D") {  // 新得分等于上一轮得分的两倍
                stk.push_back(stk[n - 1] << 1);  // 左移一位等价于乘 2
            } else if (op == "C") {  // 撤销上一轮的得分
                stk.pop_back();  // 弹出栈顶，让那一轮得分失效
            } else {  // 其余情况是数字字符串，表示本轮直接得分
                stk.push_back(stoi(op));  // 把字符串转成整数后入栈
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);  // 累加栈中全部有效得分，初值 0
    }
};