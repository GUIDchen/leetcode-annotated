// 题目：2528. 最大化城市的最小电量（Maximize the Minimum Powered City）
// 思路：二分答案 x，用差分数组 + 前缀和贪心判定：从左到右扫，电量不足就把新电站建在尽量靠右的位置。
// 时间复杂度：O(n log 1e12)，二分约 41 次、每次 O(n) 判定；空间复杂度：O(n)，差分与前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxPower(vector<int>& stations, int r, int k) {  // stations：各城初始电量；r：供电半径；k：可额外增加的电量总数
        int n = stations.size();  // 城市数量
        long long d[n + 1];  // 差分数组，长度多开 1，这样 right+1 处做减法不会越界
        memset(d, 0, sizeof d);  // 差分数组整体清零
        for (int i = 0; i < n; ++i) {  // 把每座城市已有的电量转换成一次区间加法
            int left = max(0, i - r), right = min(i + r, n - 1);  // 第 i 座城市为半径 r 内的城市供电，覆盖区间是 [left, right]（注意别越界）
            d[left] += stations[i];  // 差分：区间左端加上这份电量
            d[right + 1] -= stations[i];  // 差分：区间右端的下一位减掉，保证只有该区间受影响
        }  // 区间加法构造结束
        long long s[n + 1];  // 前缀和数组：s[i] 就是第 i 座城市当前的初始总电量
        s[0] = d[0];  // 前缀和第 0 项直接取自差分首项
        for (int i = 1; i < n + 1; ++i) {  // 从第 1 项开始往右累加
            s[i] = s[i - 1] + d[i];  // 前缀和递推，把差分还原成每座城实际电量
        }  // 前缀和计算结束
        auto check = [&](long long x, int k) {  // 二分判定函数：能否用 k 次加电让所有城市电量都 >= x
            memset(d, 0, sizeof d);  // 复用差分数组，先重新清零
            long long t = 0;  // t 记录当前城市因前面新建电站累计得到的电量
            for (int i = 0; i < n; ++i) {  // 从最左边的城市开始贪心处理
                t += d[i];  // 把差分还原成当前城市得到的增量
                long long dist = x - (s[i] + t);  // 距离目标 x 还差多少电
                if (dist > 0) {  // 电量不足，必须补电
                    if (k < dist) {  // 剩余可加电量不够，该目标值不可行
                        return false;  // 判定失败
                    }  // if 分支结束
                    k -= dist;  // 扣掉这次补的电量
                    int j = min(i + r, n - 1);  // 新电站建在 j：尽量靠右，使覆盖区间覆盖当前城市的同时还能照顾更右边的城市
                    int left = max(0, j - r), right = min(j + r, n - 1);  // 新电站实际覆盖区间 [left, right]，同样要防止越界
                    d[left] += dist;  // 差分：新电站电量加到区间左端
                    d[right + 1] -= dist;  // 差分：区间右端的下一位减掉
                    t += dist;  // 当前城市也立刻享受这部分电量，无需重新扫描
                }  // if 分支结束
            }  // 逐城检查结束
            return true;  // 所有城市都达标，说明目标可行
        };  // 判定函数定义结束
        long long left = 0, right = 1e12;  // 二分上下界：最小电量不会是负数，上界取 1e12 足以覆盖所有可能
        while (left < right) {  // 二分答案，寻找可行区间的右边界
            long long mid = (left + right + 1) >> 1;  // 上取整中点，避免 left+1==right 时死循环
            if (check(mid, k)) {  // mid 可行
                left = mid;  // 答案至少是 mid，把左边界右移
            } else {  // mid 不可行
                right = mid - 1;  // 答案严格小于 mid，把右边界左移
            }  // if 分支结束
        }  // 二分结束
        return left;  // left == right 即为最大可行的最小电量
    }  // 方法结束
};  // 类定义结束
