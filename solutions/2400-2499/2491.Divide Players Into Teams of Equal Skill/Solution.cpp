// 题目：2491. 划分技能点相等的团队（Divide Players Into Teams of Equal Skill）
// 思路：排序后双指针「最小配最大」，每组和都必须等于 skill[0]+skill[n-1]，可行则累加每组乘积，否则返回 -1。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(log n)，仅排序递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    long long dividePlayers(vector<int>& skill) {  // skill 是每个人的技能点数组，返回各团队技能乘积之和
        sort(skill.begin(), skill.end());  // 升序排序，之后用双指针让最小配最大
        int n = skill.size();  // 人数，题目保证是偶数
        int t = skill[0] + skill[n - 1];  // 由最小值和最大值先确定唯一可能的团队技能和
        long long ans = 0;  // 累加各组乘积，结果可达 1e10 量级，必须用 64 位
        for (int i = 0, j = n - 1; i < j; ++i, --j) {  // i 从左、j 从右向中间夹逼，每次组成一队
            if (skill[i] + skill[j] != t) return -1;  // 某组技能和不等于 t 就不可能划分成和相等的团队
            ans += 1ll * skill[i] * skill[j];  // 1ll 先提升为 64 位再相乘，避免 int 溢出
        }  // 当前组校验通过，继续向内收缩
        return ans;  // 返回全部团队的技能乘积之和
    }  // 方法结束
};  // 类定义结束