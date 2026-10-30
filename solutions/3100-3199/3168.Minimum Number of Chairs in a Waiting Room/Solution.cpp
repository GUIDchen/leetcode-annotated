// 题目：3168. 候诊室中的最少椅子数（Minimum Number of Chairs in a Waiting Room）
// 思路：按时间顺序模拟，维护「当前空椅子数」；有人进来而空椅子为 0 时新增一张椅子，新增总数就是历史峰值。
// 时间复杂度：O(n)，只需一次线性扫描；空间复杂度：O(1)，只用两个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumChairs(string s) {  // s 由 'E'（进门）与 'L'（离开）组成
        int cnt = 0, left = 0;  // cnt：累计分配过的椅子数；left：当前空着的椅子数
        for (char& c : s) {  // 按时间顺序处理每个事件
            if (c == 'E') {  // 有人进门
                if (left > 0) {  // 还有空椅子可以直接坐
                    --left;  // 空椅子少一张
                } else {  // 否则说明没有空椅子了
                    ++cnt;  // 只能新增一张椅子，椅子总数加一
                }  // if/else 结束
            } else {  // 否则就是 'L'，有人离开
                ++left;  // 空出一张椅子，供后面进门的人使用
            }  // else 分支结束
        }  // 字符串遍历结束
        return cnt;  // 分配过的椅子总数就是所需的最少椅子数
    }  // 方法结束
};  // 类定义结束