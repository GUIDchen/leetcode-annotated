// 题目：1776. 车队 II（Car Fleet II）
// 思路：从右向左扫描，用单调栈维护「可能被追尾」的车；栈顶若已被别人追尾过早，则当前车追不上它，弹掉；否则追尾时间就是距离除以相对速度。
// 时间复杂度：O(n)，每辆车最多入栈出栈一次；空间复杂度：O(n) 存放答案与栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {  // cars：按位置升序排列的 [位置, 速度] 列表
        int n = cars.size();  // 车的数量
        vector<double> ans(n, -1.0);  // 答案：每辆车追上前车的时间，-1 表示永远追不上
        stack<int> stk;  // 单调栈：保存“可能被某辆车追尾”的车的下标
        for (int i = n - 1; ~i; --i) {  // 从最右端向左扫描：先确定右侧车的结局，才能判断左侧车追谁
            while (stk.size()) {  // 不断检查栈顶候选，直到找到可追目标或栈空
                int j = stk.top();  // 栈顶候选前车的下标
                if (cars[i][1] > cars[j][1]) {  // 当前车更快，才有可能追上它
                    double t = (cars[j][0] - cars[i][0]) * 1.0 / (cars[i][1] - cars[j][1]);  // 追尾时间 = 距离 / 相对速度
                    if (ans[j] < 0 || t <= ans[j]) {  // 追上时前车还没追尾别人（或恰好同时），这次追尾才有效
                        ans[i] = t;  // 记录当前车的追尾时间
                        break;  // 找到有效目标就跳出
                    }
                }
                stk.pop();  // 追不上，或前车会先追尾别人：该候选不可能再被当前车追上
            }
            stk.push(i);  // 当前车入栈，成为左侧车辆的新候选目标
        }
        return ans;  // 返回每辆车的追尾时间
    }
};  // 类定义结束