// 3777. 使子字符串变交替的最少删除次数 / Minimum Deletions to Make Alternating Substring
// 核心思路：把 s[i]==s[i-1] 的位置标记为 1，区间 [l,r] 的冲突数就是这些标记的区间和；用树状数组支持单点修改与前缀和，翻转一个字符只需改动它与后一位共两个标记。
// 复杂度：时间复杂度 O((n+q) log n)，空间复杂度 O(n)，其中 n 为字符串长度，q 为操作次数。
class BinaryIndexedTree {  // 树状数组：支持单点修改与前缀和查询
public:  // 公有成员
    int n;  // 下标范围 1..n
    vector<int> c;  // 树状数组本体

    BinaryIndexedTree(int n)  // 构造函数，n 为下标上界
        : n(n)  // 记录下标范围
        , c(n + 1, 0) {}  // 数组开 n+1 个并全部置 0

    void update(int x, int delta) {  // 在下标 x 处加上 delta
        while (x <= n) {  // 沿 lowbit 一路上溯
            c[x] += delta;  // 更新当前节点
            x += x & -x;  // 跳到父节点
        }  // 上溯结束
    }  // 单点修改结束

    int query(int x) {  // 查询前缀和 [1, x]
        int s = 0;  // 累计结果
        while (x > 0) {  // 沿 lowbit 一路下降
            s += c[x];  // 累加当前节点
            x -= x & -x;  // 跳到前一个覆盖块
        }  // 下降结束
        return s;  // 返回前缀和
    }  // 查询结束
};  // 类定义结束

class Solution {  // 定义题解类
public:  // 公有成员
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {  // 返回每次查询区间子串变为交替所需的最少删除次数
        int n = s.size();  // 字符串长度
        vector<int> nums(n, 0);  // nums[i] 标记 s[i] 是否与 s[i-1] 相同
        BinaryIndexedTree bit(n);  // 用树状数组维护 nums 的前缀和

        for (int i = 1; i < n; i++) {  // 从第二个字符开始标记相邻相等的位置
            nums[i] = (s[i] == s[i - 1]);  // 相邻字符相同则标记为 1
            if (nums[i]) {  // 该位置构成一个需要删除的冲突
                bit.update(i + 1, 1);  // 在树状数组的 i+1 处加一
            }  // 分支结束
        }  // 标记结束

        vector<int> ans;  // 保存每次查询的答案

        for (auto& q : queries) {  // 依次处理每个操作
            if (q[0] == 1) {  // 类型 1：翻转 s[q[1]] 处的字符
                int j = q[1];  // 被翻转位置的下标

                int delta = (nums[j] ^ 1) - nums[j];  // 计算 nums[j] 翻转后的变化量
                nums[j] ^= 1;  // 翻转 nums[j]
                bit.update(j + 1, delta);  // 把变化量写回树状数组

                if (j + 1 < n) {  // 下一位是否为冲突也会随之改变
                    delta = (nums[j + 1] ^ 1) - nums[j + 1];  // 计算 nums[j+1] 翻转后的变化量
                    nums[j + 1] ^= 1;  // 翻转 nums[j+1]
                    bit.update(j + 2, delta);  // 把变化量写回树状数组
                }  // 边界判断结束
            } else {  // 类型 2：查询区间 [l, r] 内的冲突数
                int l = q[1];  // 区间左端点
                int r = q[2];  // 区间右端点
                ans.push_back(bit.query(r + 1) - bit.query(l + 1));  // 前缀和相减得到区间冲突数
            }  // 分支结束
        }  // 操作处理完毕
        return ans;  // 返回全部查询结果
    }  // 方法结束
};  // 类定义结束
