// 题目：1865. 找出和为指定值的下标对（Finding Pairs With a Certain Sum）
// 思路：nums1 不变、nums2 会随 add 变化，于是给 nums2 建值频次哈希表；add 时先减旧值再加新值，count 时枚举 nums1 的每个 x，累加 tot - x 在频次表中的次数。
// 时间复杂度：构造 O(n)，add O(1)，count O(len(nums1))；空间复杂度：O(len(nums2))，用于存放频次表。
class FindSumPairs {  // LeetCode 要求的 FindSumPairs 类
public:  // 构造、add、count 三个接口都需要对外可见
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {  // 构造函数：保存两个数组，并预先统计 nums2 的值频次
        this->nums1 = nums1;  // 复制 nums1（只参与配对查询，不会被修改）
        this->nums2 = nums2;  // 复制 nums2（add 会原地修改它）
        for (int x : nums2) {  // 遍历 nums2 建立频次表
            ++cnt[x];  // 数值 x 在 nums2 中的出现次数加一
        }  // 频次统计完成
    }  // 构造函数结束

    void add(int index, int val) {  // 把 nums2[index] 加上 val，同时同步维护频次表
        --cnt[nums2[index]];  // 先从频次表里去掉旧值的一次出现
        nums2[index] += val;  // 原地修改 nums2 的值
        ++cnt[nums2[index]];  // 再把新值的一次出现加进频次表
    }  // add 结束

    int count(int tot) {  // 统计有多少对 (nums1[i], nums2[j]) 的和恰好等于 tot
        int ans = 0;  // 数对计数从 0 开始
        for (int x : nums1) {  // nums2 的取值都在频次表 cnt 里，因此只需枚举 nums1
            ans += cnt[tot - x];  // 与 x 配对的另一半是 tot - x，它的出现次数就是这一轮的贡献
        }  // nums1 枚举结束
        return ans;  // 返回数对总数
    }  // count 结束

private:  // 以下为内部数据成员
    vector<int> nums1;  // nums1 的副本
    vector<int> nums2;  // nums2 的副本（会被 add 修改）
    unordered_map<int, int> cnt;  // nums2 的值频次表：键是数值，值是出现次数
};  // 类定义结束

// 下面这段是 LeetCode 判题器生成的调用示例，仅供参考，不属于题解逻辑
/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */  // 调用示例结束
