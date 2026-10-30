// 3422. 将子数组元素变为相等所需的最小操作数 / Minimum Operations to Make Subarray Elements Equal
// 核心思路：对每个长度为 k 的窗口维护左右两个有序多重集（左边元素不大于右边，右边至多多一个），以右侧最小值为中位数，按“距中位数的绝对差之和”统计代价；窗口右移时增量更新两个集合及其元素和
// 复杂度：时间 O(n·log k)，空间 O(k)（两个多重集最多共 k 个元素）
class Solution {  // 定义题解类
public:  // 公有方法区
    long long minOperations(vector<int>& nums, int k) {  // 求使每个长度 k 的子数组元素相等的最小操作数
        multiset<int> l, r;  // l 存较小的一半（含中位数），r 存较大的一半，r 至多比 l 多一个
        long long s1 = 0, s2 = 0, ans = 1e18;  // s1、s2 分别是 l、r 的元素和；ans 初值取足够大的 1e18
        for (int i = 0; i < nums.size(); ++i) {  // 枚举窗口右端点 i
            l.insert(nums[i]);  // 先把新元素放进左集合
            s1 += nums[i];  // 同步累加左集合的和
            int y = *l.rbegin();  // 取左集合的最大值，准备迁移到右集合
            l.erase(l.find(y));  // 从左集合中删除该最大值
            s1 -= y;  // 左集合元素和相应减少
            r.insert(y);  // 把它插入右集合
            s2 += y;  // 右集合元素和相应增加
            if (r.size() - l.size() > 1) {  // 保持平衡：右集合最多比左集合多一个元素
                y = *r.begin();  // 取右集合的最小值，归还给左集合
                r.erase(r.find(y));  // 从右集合中删除该最小值
                s2 -= y;  // 右集合元素和相应减少
                l.insert(y);  // 插入左集合
                s1 += y;  // 左集合元素和相应增加
            }  // 平衡调整分支结束
            if (i >= k - 1) {  // 窗口长度达到 k 时才开始统计代价
                long long x = *r.begin();  // 中位数取右集合的最小值（两个集合大小相近，中位数一定在 r 中）
                ans = min(ans, s2 - x * (int) r.size() + x * (int) l.size() - s1);  // 代价为中位数两侧的绝对差之和，用元素和公式 O(1) 算出
                int j = i - k + 1;  // 左端点下标，准备把它移出窗口以滑动
                if (r.contains(nums[j])) {  // 若待删元素在右集合
                    r.erase(r.find(nums[j]));  // 从右集合删除它
                    s2 -= nums[j];  // 右集合元素和相应减少
                } else {  // 否则该元素在左集合
                    l.erase(l.find(nums[j]));  // 从左集合删除它
                    s1 -= nums[j];  // 左集合元素和相应减少
                }  // 删除分支结束
            }  // 统计分支结束
        }  // 窗口枚举结束
        return ans;  // 返回所有窗口中代价的最小值
    }  // 方法结束
};  // 类定义结束
