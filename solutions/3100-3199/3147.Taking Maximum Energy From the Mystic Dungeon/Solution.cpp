// 题目：3147. 从魔法师身上吸取的最大能量（Taking Maximum Energy From the Mystic Dungeon）
// 思路：一次取法对应下标 i, i+k, i+2k, ... 的一段后缀，末项必定落在最后 k 个位置上；枚举末项后往前每隔 k 累加，就得到该等差数列的全部后缀和，取最大即可。
// 时间复杂度：O(n)，每个下标只会被访问一次；空间复杂度：O(1)，只用常数个额外变量。
class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {  // energy：每位魔法师的能量；k：每次跳跃的步长
        int ans = -(1 << 30);  // ans：答案初值取足够小的数，保证能被第一次更新覆盖
        int n = energy.size();  // n：数组长度
        for (int i = n - k; i < n; ++i) {  // 枚举末项 i，末项只可能落在最后 k 个位置
            for (int j = i, s = 0; j >= 0; j -= k) {  // j 从末项往前每隔 k 回退，s 维护当前后缀和
                s += energy[j];  // 把当前位置的能量累加进后缀和
                ans = max(ans, s);  // 每个后缀和都对应一种合法的取法，用它更新答案
            }
        }
        return ans;  // 返回能吸取到的最大能量
    }
};