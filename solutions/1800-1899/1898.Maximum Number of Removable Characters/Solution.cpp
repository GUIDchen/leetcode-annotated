// 题目：1898. 可移除字符的最大数目（Maximum Number of Removable Characters）
// 思路：可行性关于删除个数 k 单调不增（能删 k 个就一定也能删更少的），于是二分 k；判定时标记前 k 个删除位置，再用双指针检查 p 是否为剩余 s 的子序列。
// 时间复杂度：O((m + n) log r)，r = removable.size()；空间复杂度：O(m)，rem 标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumRemovals(string s, string p, vector<int>& removable) {  // s：原字符串；p：需仍是 s 子序列的字符串；removable：按下标顺序可删除的位置
        int m = s.size(), n = p.size();  // m、n 分别是 s 与 p 的长度
        int l = 0, r = removable.size();  // 二分答案区间 [l, r]：表示最多能删除的字符个数
        bool rem[m];  // rem[i] 标记 s 的下标 i 是否被删除

        auto check = [&](int k) {  // 判定函数：删掉前 k 个下标后，p 是否仍是 s 的子序列
            memset(rem, false, sizeof(rem));  // 每一轮判定前先把删除标记清空
            for (int i = 0; i < k; i++) {  // 标记前 k 个被删除的位置
                rem[removable[i]] = true;  // 第 i 个被删下标打上标记
            }
            int i = 0, j = 0;  // i 扫描 s，j 扫描 p，都是双指针
            while (i < m && j < n) {  // 两个指针都未越界就继续匹配
                if (!rem[i] && s[i] == p[j]) {  // s[i] 未被删除且与 p[j] 相同，匹配成功
                    ++j;  // p 的指针前进一位
                }
                ++i;  // 无论是否匹配，s 的指针都要前进
            }
            return j == n;  // p 的每个字符都被匹配到，说明 p 仍是子序列
        };
        while (l < r) {  // 二分查找最大的可行 k
            int mid = (l + r + 1) >> 1;  // 取上取整中点，配合 l = mid 避免死循环
            if (check(mid)) {  // 删掉 mid 个字符仍然可行
                l = mid;  // 答案至少是 mid，把下界抬高
            } else {  // mid 不可行
                r = mid - 1;  // 答案落在左半侧
            }
        }
        return l;  // l 与 r 重合处就是最多可删除的数目
    }
};
