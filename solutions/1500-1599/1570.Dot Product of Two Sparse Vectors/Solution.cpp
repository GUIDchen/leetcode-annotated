// 题目：1570. 两个稀疏向量的点积（Dot Product of Two Sparse Vectors）
// 思路：构造时只把非零元素存进哈希表（下标 → 值），求点积时遍历较小的那张表，查另一张表是否有同一下标并累加乘积。
// 时间复杂度：构造 O(n)；点积 O(min(非零个数))；空间复杂度：O(非零个数)，只存非零项。
class SparseVector {  // 表示稀疏向量的类
public:  // 成员对外可见
    unordered_map<int, int> d;  // 哈希表：键是非零元素的下标，值是元素值

    SparseVector(vector<int>& nums) {  // 构造函数：nums 是完整向量，只保留非零项
        for (int i = 0; i < nums.size(); ++i) {  // 逐个下标扫描
            if (nums[i]) {  // 只记录非零元素，达到“稀疏”存储的效果
                d[i] = nums[i];  // 存下下标 i 与对应的值
            }
        }
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {  // vec：另一个稀疏向量，返回两者的点积
        auto a = d;  // 复制自己的哈希表，避免后面 swap 改动成员
        auto b = vec.d;  // 复制对方哈希表
        if (a.size() > b.size()) {  // 保证 a 是元素更少的那张表
            swap(a, b);  // 交换两张表，使遍历代价更小
        }
        int ans = 0;  // 点积累加结果
        for (auto& [i, v] : a) {  // 遍历较小表里的每个「下标 → 值」
            if (b.count(i)) {  // 另一张表也有这个下标
                ans += v * b[i];  // 相同下标的值相乘后累加
            }
        }
        return ans;  // 返回点积
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);