// 题目：3072. 将元素分配到两个数组中 II（Distribute Elements Into Two Arrays II）
// 核心思路：需要动态查询「某数组中有多少个数严格大于 x」，于是先把 nums 排序离散化，再用两棵树状数组分别维护两个数组的值域计数，按规则比较两份计数结果决定元素去向。
// 时间复杂度：O(n·log n)，离散化排序 O(n·log n) 加每次 O(log n) 的树状数组操作；空间复杂度：O(n)，离散化数组、两棵树状数组与结果数组。
class BinaryIndexedTree {  // 手写树状数组（Binary Indexed Tree / Fenwick 树），支持单点加与前缀和查询
private:  // 私有区：值域大小与内部数组，外部不可直接访问
    int n;  // n：离散化后的值域大小，树状数组维护 1..n 这些下标
    vector<int> c;  // c：树状数组内部数组，c[x] 保存一段区间的计数和，下标从 1 开始

public:  // 构造与对外接口
    BinaryIndexedTree(int n)  // 构造函数：n 为值域大小
        : n(n)  // 成员初始化列表：把参数 n 存进成员变量 n
        , c(n + 1) {}  // 内部数组开到 n+1，下标 0 空置不用

    void update(int x, int delta) {  // 在位置 x 上加 delta（本题 delta 恒为 1，即计数加一）
        for (; x <= n; x += x & -x) {  // 沿 lowbit 向上更新：x += x & -x 跳到下一个覆盖 x 的节点
            c[x] += delta;  // 把增量累加到当前节点
        }
    }  // update 函数结束

    int query(int x) {  // 查询前缀和：返回下标 1..x 上的计数总和，即「值不大于 x 的元素个数」
        int s = 0;  // 累加器
        for (; x > 0; x -= x & -x) {  // 当 x 仍大于 0 时继续回退
            s += c[x];  // 累加这一段的计数
        }
        return s;  // 返回前缀和
    }
};

class Solution {  // 题解类：用两棵动态计数树模拟两数组的分配过程
public:  // 题解方法对外可见
    vector<int> resultArray(vector<int>& nums) {  // nums：输入数组；返回按规则分配后拼接得到的数组
        vector<int> st = nums;  // 拷贝一份用于排序，得到所有取值构成的升序序列，作为离散化值域
        sort(st.begin(), st.end());  // 排序后，某个值在 st 中的下标就可以代表它的大小排名
        int n = st.size();  // n 同时也是待处理元素的总个数
        BinaryIndexedTree tree1(n + 1);  // arr1 对应的树状数组：维护 arr1 中每个离散化取值的出现次数
        BinaryIndexedTree tree2(n + 1);  // arr2 对应的树状数组
        tree1.update(distance(st.begin(), lower_bound(st.begin(), st.end(), nums[0])) + 1, 1);  // 把 nums[0] 的排名（lower_bound 得 0 基下标，加一变成 1 基）在 tree1 中计数加一
        tree2.update(distance(st.begin(), lower_bound(st.begin(), st.end(), nums[1])) + 1, 1);  // 把 nums[1] 的排名在 tree2 中计数加一
        vector<int> arr1 = {nums[0]};  // arr1 以第一个元素起步
        vector<int> arr2 = {nums[1]};  // arr2 以第二个元素起步
        for (int k = 2; k < n; ++k) {  // 从下标 2 开始依次分配剩余元素
            int x = distance(st.begin(), lower_bound(st.begin(), st.end(), nums[k])) + 1;  // 求出当前元素的离散化排名（1 基下标）
            int a = arr1.size() - tree1.query(x);  // arr1.size() - query(x) 就是 arr1 中严格大于当前值的元素个数（query 统计的是不大于 x 的个数）
            int b = arr2.size() - tree2.query(x);  // 同理得到 arr2 中严格大于当前值的元素个数
            if (a > b) {  // arr1 中更大元素更多，就把当前元素放进 arr1
                arr1.push_back(nums[k]);  // 追加到 arr1 末尾
                tree1.update(x, 1);  // 同步更新 tree1 计数，保证后续查询正确
            } else if (a < b) {  // arr2 中更大元素更多，则放进 arr2
                arr2.push_back(nums[k]);  // 追加到 arr2 末尾
                tree2.update(x, 1);  // 同步更新 tree2 计数
            } else if (arr1.size() <= arr2.size()) {  // 两者数量相等时，按规则优先放进元素更少的数组；长度也相等则放进 arr1
                arr1.push_back(nums[k]);  // 追加到 arr1 末尾
                tree1.update(x, 1);  // 同步更新 tree1 计数
            } else {  // 否则 arr1 元素更多，放进 arr2
                arr2.push_back(nums[k]);  // 追加到 arr2 末尾
                tree2.update(x, 1);  // 同步更新 tree2 计数
            }
        }
        arr1.insert(arr1.end(), arr2.begin(), arr2.end());  // 把 arr2 接到 arr1 末尾，得到最终结果
        return arr1;  // 返回拼接后的数组
    }
};