// 题目：920. 播放列表的数量（Number of Music Playlists）
// 思路：DP，f[i][j] 表示播放 i 首、恰好用到 j 首不同歌曲的方案数；第 i 首放新歌或放旧歌两类转移。
// 时间复杂度：O(goal*n)，双重循环；空间复杂度：O(goal*n)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numMusicPlaylists(int n, int goal, int k) {  // n 为不同歌曲数，goal 为播放列表长度，k 为同一首歌的最小间隔
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        long long f[goal + 1][n + 1];  // f[i][j]：播放 i 首歌、恰好用到 j 首不同歌曲的方案数
        memset(f, 0, sizeof(f));  // 全部清零
        f[0][0] = 1;  // 边界：0 首歌用 0 首不同歌，只有 1 种空方案
        for (int i = 1; i <= goal; ++i) {  // 逐首决定第 i 首歌
            for (int j = 1; j <= n; ++j) {  // 枚举到第 i 首为止已用到的不同歌曲数 j
                f[i][j] = f[i - 1][j - 1] * (n - j + 1);  // 第 i 首是新歌：共 n 首，已用过 j-1 首，还剩 n-j+1 种选择
                if (j > k) {  // 只有不同歌数 j 大于 k 时，才可能重复播放旧歌
                    f[i][j] += f[i - 1][j] * (j - k);  // 第 i 首是旧歌：最近 k 首不能重复，故有 j-k 种选择
                }  // 结束 if (j > k)
                f[i][j] %= mod;  // 取模，防止中间结果溢出
            }  // 结束内层循环
        }  // 结束外层循环
        return f[goal][n];  // 返回播放 goal 首且恰好用满 n 首歌的方案数
    }  // 结束 numMusicPlaylists 方法
};  // 结束 Solution 类