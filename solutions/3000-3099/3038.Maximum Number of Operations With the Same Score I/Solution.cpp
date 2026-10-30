// 题目：3038. 相同分数的最大操作数目 I（Maximum Number of Operations With the Same Score I）
// 思路：每轮删除首两个或尾两个且分数必须全部相同；首两个元素之和先定下目标分数，之后从前往后每两个一组检查即可。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxOperations(vector<int>& nums) {  // nums：输入数组，长度至少为 2
        int s = nums[0] + nums[1];  // 题目保证长度不少于 2；第一对元素的分数就固定了后续所有操作的分数
        int ans = 0, n = nums.size();  // ans 记录操作次数，n 是数组长度
        for (int i = 0; i + 1 < n && nums[i] + nums[i + 1] == s; i += 2) {  // 从前往后每两个一组，剩余不足两个或分数不同就停止
            ++ans;  // 当前这一对可以按目标分数删除，操作次数加一
        }
        return ans;  // 返回最多可执行的操作次数
    }
};