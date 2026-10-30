// 题目：565. 数组嵌套（Array Nesting）
// 思路：nums 是 0..n-1 的排列，按 nums[i] 不断跳转会形成若干个互不相交的环；用 vis 标记已走过的下标，每个环只遍历一次并取最大长度。
// 时间复杂度：O(n)，每个下标至多被访问一次；空间复杂度：O(n)，vis 标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int arrayNesting(vector<int>& nums) {  // nums 是 0..n-1 的排列，返回所有环中的最大长度
        int n = nums.size();  // n 是数组长度，也是下标范围
        vector<bool> vis(n);  // vis[i] 标记下标 i 是否已经被某个环遍历过
        int res = 0;  // res 记录目前发现的最大环长度
        for (int i = 0; i < n; ++i) {  // 枚举每个下标作为环的起点
            if (vis[i]) continue;  // 已访问过的下标属于之前的环，跳过可保证线性时间
            int cur = nums[i], m = 1;  // 从 nums[i] 开始，m 记录当前环的节点数（含起点）
            vis[cur] = true;  // 标记环上的第一个节点
            while (nums[cur] != nums[i]) {  // 沿 nums 跳转，直到回到起点的值（环闭合）
                cur = nums[cur];  // 跳到下一个下标
                ++m;  // 环长度加一
                vis[cur] = true;  // 标记新到达的节点
            }  // 环遍历结束
            res = max(res, m);  // 用当前环长度更新最大值
        }  // 所有起点枚举结束
        return res;  // 返回最大环长度
    }  // 方法结束
};