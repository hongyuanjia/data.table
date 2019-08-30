
# data.table <a href="http://r-datatable.com"><img src="logo.png" align="right" height="140" /></a>

<!-- badges: start -->
[![CRAN status](https://www.r-pkg.org/badges/version/data.table)](https://cran.r-project.org/web/checks/check_results_data.table.html)
[![Travis build status](https://travis-ci.org/Rdatatable/data.table.svg?branch=master)](https://travis-ci.org/Rdatatable/data.table)
[![AppVeyor build status](https://ci.appveyor.com/api/projects/status/kayjdh5qtgymhoxr/branch/master?svg=true)](https://ci.appveyor.com/project/Rdatatable/data-table)
[![Codecov test coverage](https://codecov.io/github/Rdatatable/data.table/coverage.svg?branch=master)](https://codecov.io/github/Rdatatable/data.table?branch=master)
[![GitLab CI build status](https://gitlab.com/Rdatatable/data.table/badges/master/pipeline.svg)](https://gitlab.com/Rdatatable/data.table/pipelines)
[![Downloads](https://cranlogs.r-pkg.org/badges/data.table)](https://www.rdocumentation.org/trends)
[![Depsy](http://depsy.org/api/package/cran/data.table/badge.svg)](http://depsy.org/package/r/data.table)
[![CRAN usage](https://jangorecki.gitlab.io/rdeps/data.table/CRAN_usage.svg?sanitize=true)](https://gitlab.com/jangorecki/rdeps)
[![BioC usage](https://jangorecki.gitlab.io/rdeps/data.table/BioC_usage.svg?sanitize=true)](https://gitlab.com/jangorecki/rdeps)
[![Indirect depends](https://jangorecki.gitlab.io/rdeps/data.table/indirect_depends.svg?sanitize=true)](https://gitlab.com/jangorecki/rdeps)
<!-- badges: end -->

`data.table` provides a high-performance version of [base R](https://www.r-project.org/about.html)'s `data.frame` (columnar, rectangular, in-memory data structure) with syntax and feature enhancements for ease of use, convenience and programming speed.

## Why `data.table`?

* **Concise syntax** -- fast to type, fast to read
* **Computational performance** -- execution speed and memory efficiency
* **Feature richness** -- wide variety of built-in tools for the real world data guru
* **Feature stability** -- careful API lifecycle management
* **Supportive community** -- maintainers and enthusiasts excited to help

## Features

* Fast and friendly delimited **file reader**: **`?fread`**, see also [convenience features for _small_ data](https://github.com/Rdatatable/data.table/wiki/Convenience-features-of-fread)
* Fast and feature-rich delimited **file writer**: **`?fwrite`**
* Low-level **parallelism** out of the box: many common operations are internally parallelized to automatically use multiple CPU threads
* Fast and scalable **aggregations**: e.g. 100GB in RAM (see [benchmarks](https://h2oai.github.io/db-benchmark/) on up to **two billion rows**)
* Fast and feature-rich **joins**: **ordered joins** (e.g. rolling forwards, backwards, nearest and limited-staleness), **[overlapping range joins](https://github.com/Rdatatable/data.table/wiki/talks/EARL2014_OverlapRangeJoin_Arun.pdf)** (similar to `IRanges::findOverlaps`), **[non-equi joins](https://github.com/Rdatatable/data.table/wiki/talks/ArunSrinivasanUseR2016.pdf)** (i.e. joins using operators `>`, `>=`, `<`, `<=`), **aggregate-on -join** (`by=.EACHI`), **update-on-join**
* Fast add/update/delete columns **by reference** (including by group) using no copies at all (memory efficient)
* Fast and feature-rich data **reshaping**: **`?dcast`** (_pivot/wider/spread_) and **`?melt`** (_unpivot/longer/gather_)
* **Any R function from any R package** can be used in queries -- not just the subset of functions made available by (e.g.) a database backend, also columns of type `list` are supported (akin to `array`/`map` types in SQL)
* **[No dependencies](https://en.wikipedia.org/wiki/Dependency_hell)** at all other than base R itself, for simpler/lightweight production/maintenance
* **Upstream API stability**: the R dependency is **as old as possible for as long as possible** and we continuously test against that version; e.g. v1.11.0 released on 5 May 2018 bumped the dependency up from 5 year old R 3.0.0 to then-4 year old R 3.1.0
* **Downstream API stability**: major breaking changes are enforced only slowly (e.g. several years) so that old code continues to work with minimal refactoring

## Installation

``` r
install.packages("data.table")
```

### Development version

```r
install.packages("data.table", repos="https://Rdatatable.gitlab.io/data.table")
```

To update your development version if a newer revision is available:

```r
data.table::update.dev.pkg()
```

See [the Installation wiki](https://github.com/Rdatatable/data.table/wiki/Installation) for more details.

## Usage

Use the `data.table` subset `[` operator the same way you would use it for `data.frame`, but...

* No need to prefix columns with `DT$` anywhere inside `[ ]`
* Any valid expression is allowed in `j` (2nd) argument
* Extra (3rd) argument `by` to compute `j` by group

```r
library(data.table)
DT = as.data.table(iris)

# General query mindframe:
# FROM[WHERE, SELECT, GROUP BY]
# DT  [i,     j,      by]

# Filter, average by group
DT[Petal.Width > 1.0, mean(Petal.Length), by = Species]
#      Species       V1
#1: versicolor 4.362791
#2:  virginica 5.552000

# Sort by Petal.Width (increasing) and then take the first 5 rows (chaining)
DT[order(Petal.Width)][1:5]
#    Sepal.Length Sepal.Width Petal.Length Petal.Width Species
# 1:          4.9         3.1          1.5         0.1  setosa
# 2:          4.8         3.0          1.4         0.1  setosa
# 3:          4.3         3.0          1.1         0.1  setosa
# 4:          5.2         4.1          1.5         0.1  setosa
# 5:          4.9         3.6          1.4         0.1  setosa
```

### Getting started

* [Introduction to data.table](https://cloud.r-project.org/web/packages/data.table/vignettes/datatable-intro.html) vignette
* [Getting started](https://github.com/Rdatatable/data.table/wiki/Getting-started) wiki page

### Cheatsheets

<a href="https://github.com/rstudio/cheatsheets/raw/master/datatable.pdf"><img src="cheatsheet.png" width="615" height="242"/></a>

## Community

`data.table` is widely used by the R community. As of July 2019, it was used by over 680 CRAN and Bioconductor packages and was the [9th most starred](http://www.r-pkg.org/starred) R package on GitHub. If you need help, the `data.table` community is active StackOverflow, with nearly 87% of [9,000 questions](http://stackoverflow.com/questions/tagged/data.table) answered (vs. 82% overall for R).

### Stay up-to-date

- Click the **Watch** button at the top and right of GitHub project page
- Read the [NEWS file](NEWS.md) (updated with every new feature/bug fix)
- Follow [#rdatatable](https://twitter.com/hashtag/rdatatable) on Twitter
- Watch recent [Presentations](https://github.com/Rdatatable/data.table/wiki/Presentations)
- Read recent [Articles](https://github.com/Rdatatable/data.table/wiki/Articles)

### Contributing

Guidelines for filing issues / pull requests: [Contribution Guidelines](https://github.com/Rdatatable/data.table/wiki/Contributing).
