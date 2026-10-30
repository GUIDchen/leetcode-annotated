// 题目：2868. 单词游戏（The Wording Game）
// 思路：按规则模拟轮流出词：双方各自的单词表已排序，指针各自向前推进；能接的词要么同首字母且字典序更大，要么首字母恰好大 1，某一方无词可接即判负。
// 时间复杂度：O(n + m)，两个指针各自只把数组扫一遍；空间复杂度：O(1)，只用了下标与一个当前单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canAliceWin(vector<string>& a, vector<string>& b) {  // a 是 Alice 的词表，b 是 Bob 的词表，均已升序
        int i = 1, j = 0, k = 1;  // i/j 分别是 a、b 下一个待考察下标；k=1 表示轮到 Bob（Alice 已用 a[0] 开局）
        string w = a[0];  // w 是桌面上最后一个被打出的单词，Alice 先出最小的那个
        while (1) {  // 双方交替进行，直到某个人无词可出才在分支里 return
            if (k) {  // 轮到 Bob 出词
                if (j == b.size()) {  // Bob 的词已经全部试过，没有可接的词
                    return true;  // Bob 无法出词，Alice 获胜
                }
                if ((b[j][0] == w[0] && w < b[j]) || b[j][0] - w[0] == 1) {  // 同首字母且更大，或首字母恰好大 1 才合法
                    w = b[j];  // 合法就把这个词打到桌面上，成为新的当前词
                    k ^= 1;  // 切换回合，交还给 Alice
                }
                ++j;  // 无论是否用上，Bob 的词表指针都只前进，跳过不可能再用的词
            } else {  // 轮到 Alice 出词
                if (i == a.size()) {  // Alice 的词已经全部试过，没有可接的词
                    return false;  // Alice 无法出词，她输了
                }
                if ((a[i][0] == w[0] && w < a[i]) || a[i][0] - w[0] == 1) {  // 同样的合法性判断：同首字母更大或首字母大 1
                    w = a[i];  // 合法就更新桌面上的当前词
                    k ^= 1;  // 切换回合，交还给 Bob
                }
                ++i;  // Alice 的词表指针向前推进一位
            }
        }
    }
};