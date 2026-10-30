// 题目：735. 小行星碰撞（Asteroid Collision）
// 思路：用栈模拟碰撞——正数直接入栈；负数则循环撞碎比自己小的栈顶正数，遇到相等者同归于尽，威胁清空后自身入栈。
// 时间复杂度：O(n)，每个小行星最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个小行星。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> asteroidCollision(vector<int>& asteroids) {  // asteroids：按飞行顺序排列的小行星（正数向右、负数向左）
        vector<int> stk;  // 用 vector 模拟栈，保存碰撞后仍然存活、且从左到右不会再相撞的星球
        for (int x : asteroids) {  // 按给定顺序从左到右处理每个小行星
            if (x > 0) {  // 正数向右飞，不会主动撞到左边的星球，直接入栈等待
                stk.push_back(x);  // 入栈，成为右侧星球可能的碰撞对象
            } else {  // x < 0：向左飞，可能与栈顶向右飞的星球相撞
                while (stk.size() && stk.back() > 0 && stk.back() < -x) {  // 栈顶向右且体积更小 → 栈顶被撞碎；循环直到栈空或撞不动
                    stk.pop_back();  // 弹出被撞碎的栈顶星球
                }  // 循环结束：栈空 / 栈顶向左（不会相撞）/ 栈顶向右且不小于当前星球
                if (stk.size() && stk.back() == -x) {  // 栈顶与当前星球大小相同：两者同归于尽
                    stk.pop_back();  // 弹出栈顶，当前星球也一起消失，不再入栈
                } else if (stk.empty() || stk.back() < 0) {  // 栈空或栈顶也向左飞：两者永远不会相撞，当前星球存活
                    stk.push_back(x);  // 当前星球入栈，继续向右推进
                }  // 其余情况（栈顶向右且更大）：当前星球被撞碎，直接丢弃
            }  // 结束 if / else 分支
        }  // 结束对所有小行星的遍历
        return stk;  // 栈中剩下的元素就是最终稳定状态
    }  // 结束 asteroidCollision
};  // 结束 Solution 类