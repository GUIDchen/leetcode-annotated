// 题目：2214. 通关游戏所需的最低生命值（Minimum Health to Beat Game）
// 思路：总伤害为 sum(damage)，护甲只能在承受某一次伤害时减免，所以一定把它用最大的一次伤害上，实际减免 min(max(damage), armor)；生命值需严格大于总损失，故最后再加 1。
// 时间复杂度：O(n)，一次遍历同时求总和与最大值；空间复杂度：O(1)，只用了两个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumHealth(vector<int>& damage, int armor) {  // damage：每一关的伤害；armor：护甲值；返回通关所需的最低初始生命值
        long long s = 0;  // s 累加所有关卡的伤害，用 long long 防止多关相加溢出 int
        int mx = damage[0];  // mx 记录单次最大伤害，先取第一个元素（题目保证数组非空）
        for (int& v : damage) {  // 用引用遍历避免拷贝，逐个读取本关伤害 v
            s += v;  // 把本关伤害累加进总伤害
            mx = max(mx, v);  // 维护遍历到当前位置为止的最大单次伤害
        }
        return s - min(mx, armor) + 1;  // 总伤害减去护甲在最大一击上的减免上限，再 +1 使生命值严格大于总损失
    }
};