// 题目：2591. 将钱分给最多的儿童（Distribute Money to Maximum Children）
// 思路：先排除分不均的 -1 与钱多到必须有人拿 9 元的两种边界，再单独处理「剩 4 元必须拆成 3+1」的特例，最后按每组 8 元贪心算组数。
// 时间复杂度：O(1)，只做常数次算术运算；空间复杂度：O(1)，只用几个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distMoney(int money, int children) {  // money 是总金额，children 是儿童人数
        if (money < children) {  // 每人至少 1 元，钱不够分就无解
            return -1;  // 按题意返回 -1
        }
        if (money > 8 * children) {  // 钱多到每人发 8 元还有剩，剩下的只能加给某一人，导致最多只有 children-1 人拿到正好 8 元
            return children - 1;  // 少一个人达标
        }
        if (money == 8 * children - 4) {  // 差 4 元才能让所有人都拿 8 元：无论怎么分配都必然出现一个 3 元或 9 元的人
            return children - 2;  // 因此最多只有 children-2 人拿到 8 元
        }
        // money-8x >= children-x, x <= (money-children)/7
        return (money - children) / 7;  // 设 x 人拿 8 元，剩余 children-x 人各至少 1 元，解得 x 的上界并向下取整
    }
};