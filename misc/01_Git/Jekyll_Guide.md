# How to use Jekyll with Github Pages

## Part 1 - Fork a Jekyll Theme
- Enable [GitHub Pages](https://docs.github.com/en/pages/quickstart)
- Find a theme on [Jekyllthemes.io](https://jekyllthemes.io/)
- Fork a theme called [Contrast](https://jekyllthemes.io/theme/contrast) with name faradawn.github.io

## Part 2 - Install Jekyll on MacOS
```
# install rudy and jekyll
brew install ruby
sudo gem install jekyll bundler

# go to folder
bundle config set --local path 'vendor/bundle'
bundle install
bundle exec jekyll serve

# remember to gitignore vendor
```
