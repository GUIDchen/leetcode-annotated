// 题目：3134. 找出唯一性数组的中位数（Find the Median of the Uniqueness Array）
// 思路：二分答案 mx，再用滑动窗口统计「不同元素个数不超过 mx」的子数组个数，与中位数位置比较后收缩二分区间。
// 时间复杂度：O(n log n)，外层二分 O(log n) 次、每次滑窗 O(n)；空间复杂度：O(n)，哈希表最多保存 n 个不同的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int medianOfUniquenessArray(vector<int>& nums) {  // nums 是原数组，函数返回所有子数组唯一性值的中位数
        int n = nums.size();  // 数组长度
        using ll = long long;  // 给 long long 起短名字，子数组总数会超过 int
        ll m = (1LL + n) * n / 2;  // 唯一性数组的长度就是子数组总数 n*(n+1)/2
        int l = 0, r = n;  // 二分区间：答案（不同元素个数）落在 [0, n]
        auto check = [&](int mx) -> bool {  // 内部 lambda：判断值不超过 mx 的子数组是否已达到中位数位置
            unordered_map<int, int> cnt;  // 哈希表统计滑动窗口内各元素的出现次数
            ll k = 0;  // k 累计不同元素个数不超过 mx 的子数组个数
            for (int l = 0, r = 0; r < n; ++r) {  // 右端点 r 逐步右移扩展窗口（此处的 l、r 是窗口指针，遮蔽了外层变量）
                int x = nums[r];  // 新进入窗口的元素
                ++cnt[x];  // 该元素计数加一
                while (cnt.size() > mx) {  // 不同元素个数超过上限，需要收缩左边界
                    int y = nums[l++];  // 取出左端点元素，并把左指针右移
                    if (--cnt[y] == 0) {  // 该元素计数减到 0
                        cnt.erase(y);  // 从哈希表删除，保证 size() 恰好等于不同元素个数
                    }  // 计数减到 0 分支结束
                }  // 收缩窗口结束
                k += r - l + 1;  // 以 r 结尾的合法子数组共有 r-l+1 个
                if (k >= (m + 1) / 2) {  // 已达到中位数位置（1 基第 (m+1)/2 个）
                    return true;  // 可以提前判定 mx 可行
                }  // 提前返回分支结束
            }  // 右端点扫描结束
            return false;  // 全部扫完仍不够，说明中位数大于 mx
        };  // lambda 定义结束
        while (l < r) {  // 在 [l, r] 上二分最小的可行值
            int mid = (l + r) >> 1;  // 取中点
            if (check(mid)) {  // mid 可行，说明中位数不大于 mid
                r = mid;  // 答案缩小到左半区间（含 mid）
            } else {  // 否则 mid 不可行
                l = mid + 1;  // 答案落在右半区间（不含 mid）
            }  // if / else 分支结束
        }  // 二分结束
        return l;  // 此时 l 就是最小的可行值，即中位数
    }  // 方法体结束
};  // 类定义结束