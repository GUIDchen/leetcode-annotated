// 题目：2736. 最大和查询（Maximum Sum Queries）
// 思路：离线处理，询问按 x 从大到小排序；把 nums1 满足 ≥ x 的元素逐个插入以 nums2 秩为下标的树状数组，树状数组维护前缀最大值（即 value = nums1+nums2），再用前缀查询回答 nums2 ≥ y 的部分。
// 时间复杂度：O((n+m)log n)，各一次排序再加每元素 log n 次更新/查询；空间复杂度：O(n+m)，树状数组 O(n) 加索引与答案数组 O(m)。
class BinaryIndexedTree {  // 树状数组（下标 1..n），维护前缀最大值
private:  // 内部实现细节不对外暴露
    int n;  // 数组长度，也是树状数组合法下标的上界
    vector<int> c;  // 树状数组本体，c[i] 保存一段区间的最大值

public:  // 对外提供构造、单点更新与前缀查询
    BinaryIndexedTree(int n) {  // 构造函数：共 n 个可更新的位置
        this->n = n;  // 保存长度，update/query 都要用到
        c.resize(n + 1, -1);  // 多开一位让下标从 1 开始，统一初始化为 -1 表示该位置还没有元素
    }  // 构造函数结束

    void update(int x, int v) {  // 单点更新：把位置 x 的值变为 max(原值, v)，并向上更新所有覆盖它的节点
        while (x <= n) {  // 沿 lowbit 链向上跳，覆盖所有包含位置 x 的区间
            c[x] = max(c[x], v);  // 只求最大值，插入顺序无所谓，直接取 max 即可
            x += x & -x;  // lowbit 技巧：x & -x 是 x 最低位的 1，加上它跳到下一个负责 x 的节点
        }  // while 循环结束
    }  // update 方法结束

    int query(int x) {  // 查询前缀 [1, x] 的最大值
        int mx = -1;  // 前缀最大值的初值用 -1，表示这个前缀范围内没有任何元素
        while (x > 0) {  // 沿 lowbit 链向下跳，把前缀拆成若干个区间块
            mx = max(mx, c[x]);  // 合并当前块的最大值
            x -= x & -x;  // 减去 lowbit，跳到下一个更小的前缀块
        }  // while 循环结束
        return mx;  // 返回前缀 [1, x] 的最大值
    }  // query 方法结束
};  // 树状数组类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {  // nums1/nums2：两个等长数组；queries：若干 (x, y) 询问，求满足 nums1[i]>=x 且 nums2[i]>=y 的最大 nums1[i]+nums2[i]
        vector<pair<int, int>> nums;  // 把每对元素打包成 (-nums1[i], nums2[i])，取负后升序排序等价于按 nums1 降序
        int n = nums1.size(), m = queries.size();  // n：元素个数；m：询问个数
        for (int i = 0; i < n; ++i) {  // 逐对打包两个数组的对应元素
            nums.emplace_back(-nums1[i], nums2[i]);  // 第一分量存 nums1 的相反数，第二分量存 nums2
        }  // 打包循环结束
        sort(nums.begin(), nums.end());  // 排序后 nums 按 nums1 从大到小排列，nums2 相同时从小到大
        sort(nums2.begin(), nums2.end());  // 把 nums2 单独升序排序，用于把 nums2 的取值离散化成树状数组下标
        vector<int> idx(m);  // idx 记录询问的原始下标，离线排序后靠它把答案回填到正确位置
        iota(idx.begin(), idx.end(), 0);  // 依次填入 0, 1, ..., m-1
        sort(idx.begin(), idx.end(), [&](int i, int j) { return queries[j][0] < queries[i][0]; });  // 按询问的 x 从大到小处理：这样已插入元素集合只增不减，可以用一个指针持续前进
        vector<int> ans(m);  // 答案数组，下标与 queries 一致
        int j = 0;  // 扫描指针：指向下一个待加入树状数组的 nums 元素
        BinaryIndexedTree tree(n);  // 以离散化后的 nums2 秩为下标建立树状数组，初值 -1 表示暂无元素
        for (int i : idx) {  // 按 x 从大到小依次回答每个询问
            int x = queries[i][0], y = queries[i][1];  // 取出当前询问的两个阈值 x 与 y
            for (; j < n && -nums[j].first >= x; ++j) {  // 把所有 nums1 >= x 的元素一次性插入树状数组（因为是降序处理，j 只向前走）
                int k = nums2.end() - lower_bound(nums2.begin(), nums2.end(), nums[j].second);  // 把 nums2 由小到大的名次翻转成由大到小的秩，这样 nums2 >= y 对应前缀 [1, k]
                tree.update(k, -nums[j].first + nums[j].second);  // 插入该元素的 value = nums1 + nums2（nums1 已存成相反数，所以取负还原）
            }  // 插入循环结束
            int k = nums2.end() - lower_bound(nums2.begin(), nums2.end(), y);  // 求阈值 y 对应的秩，nums2 >= y 的所有元素恰好落在前缀 [1, k] 内
            ans[i] = tree.query(k);  // 查询前缀最大值即为当前询问答案；查不到时树状数组返回 -1
        }  // 询问循环结束
        return ans;  // 按原询问顺序返回所有答案
    }  // 方法体结束
};  // 类定义结束