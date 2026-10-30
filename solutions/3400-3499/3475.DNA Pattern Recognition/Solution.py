# 3475. DNA Pattern Recognition / 3475. DNA 模式识别
# 核心思路：用 pandas 的 str.startswith / endswith / contains 分别判断四种 DNA 模式，转成 0/1 后按 sample_id 排序返回。
# 复杂度：时间 O(n * L)（n 为样本数、L 为序列长度），空间 O(n)。

import pandas as pd  # 导入 pandas 并简写为 pd


def analyze_dna_patterns(samples: pd.DataFrame) -> pd.DataFrame:  # 为每个样本追加四个模式识别结果列
    samples["has_start"] = samples["dna_sequence"].str.startswith("ATG").astype(int)  # 序列以 ATG 开头则 has_start 置 1
    samples["has_stop"] = (  # has_stop 列：序列是否以终止密码子结尾
        samples["dna_sequence"].str.endswith(("TAA", "TAG", "TGA")).astype(int)  # 结尾匹配 TAA / TAG / TGA 之一则置 1
    )  # 多行赋值语句结束
    samples["has_atat"] = samples["dna_sequence"].str.contains("ATAT").astype(int)  # 含子串 ATAT 则 has_atat 置 1
    samples["has_ggg"] = samples["dna_sequence"].str.contains("GGG+").astype(int)  # 含三个及以上连续 G（GGG+）则 has_ggg 置 1
    return samples.sort_values(by="sample_id").reset_index(drop=True)  # 按 sample_id 升序排序并重置索引后返回
