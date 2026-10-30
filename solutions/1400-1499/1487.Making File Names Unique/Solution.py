# 题目：1487. 保证文件名唯一（Making File Names Unique）
# 核心思路：字典记下每个名字已用到的后缀编号，重名时从该编号起递增试探，直到拼出的名字未被占用。
# 时间复杂度：O(n·L)（L 为名字长度，计数整体摊还后接近线性）；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def getFolderNames(self, names: List[str]) -> List[str]:  # names 为原始文件名列表，返回保证唯一后的列表
        d = defaultdict(int)  # 字典：文件名 → 下一个可尝试的后缀编号，缺省为 0
        for i, name in enumerate(names):  # 按下标遍历，便于原地改写 names[i]
            if name in d:  # 该名字已被占用，必须加后缀
                k = d[name]  # 从上次记录的位置开始试编号
                while f'{name}({k})' in d:  # 候选后缀名也被占用就继续递增
                    k += 1  # 编号加一
                d[name] = k + 1  # 记住下次应从 k+1 开始，避免重复扫描
                names[i] = f'{name}({k})'  # 把原名改写成带后缀的唯一名字
            d[names[i]] = 1  # 标记最终名字已被占用（值 1 只作占位）
        return names  # 返回保证唯一后的文件名列表
