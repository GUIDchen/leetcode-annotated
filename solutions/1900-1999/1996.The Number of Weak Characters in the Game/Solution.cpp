// 题目：1996. 游戏中弱角色的数量（The Number of Weak Characters in the Game）
// 思路：按攻击力降序排序，攻击力相同时防御力升序；再线性扫描，用前缀最大防御力判断弱角色。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(log n)，原地排序的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfWeakCharacters(vector<vector<int>>& properties) {  // properties：每个元素是 [攻击力, 防御力]
        sort(properties.begin(), properties.end(), [&](auto& a, auto& b) { return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0]; });  // 攻击力降序；同攻击力时防御力升序，避免同攻击力角色互相误判
        int ans = 0, mx = 0;  // ans 统计弱角色个数；mx 记录已扫描过的最大防御力
        for (auto& x : properties) {  // 按攻击力从大到小遍历每个角色
            ans += x[1] < mx;  // 防御力小于此前最大值，说明前面存在攻防都严格更大的角色，当前角色为弱角色
            mx = max(mx, x[1]);  // 用当前防御力更新最大值，供后面的角色比较
        }
        return ans;  // 返回弱角色总数
    }
};