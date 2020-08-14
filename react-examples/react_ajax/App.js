import React from 'react';
import './App.css';

class Nav extends React.Component {
  state = {
    list: [],
  };

  render() {
    var listTag = [];
    for (var i = 0; i < this.props.list.length; i++) {
      var li = this.props.list[i];
      listTag.push(
        <li key={i}>
          <a
            href={li.id}
            data-id={li.id}
            onClick={(e) => {
              e.preventDefault();
              this.props.onClick(e.target.dataset.id);
            }}
          >
            {li.title}
          </a>
        </li>
      );
    }
    return (
      <nav>
        <ul>{listTag}</ul>
      </nav>
    );
  }
}

class Article extends React.Component {
  render() {
    return (
      <article>
        <h2>{this.props.title}</h2>
        {this.props.desc}
      </article>
    );
  }
}

class NowLoading extends React.Component {
  render() {
    return <h1>Loding...</h1>;
  }
}

class App extends React.Component {
  state = {
    article: {
      item: { title: 'Welcome', desc: 'Hello, React & Ajax' },
      isLoading: false,
    },
    list: {
      items: [],
      isLoading: false,
    },
  };

  componentDidMount() {
    var newList = Object.assign({}, this.state.list, { isLoading: true });
    this.setState({
      list: newList,
    });
    fetch('list.json')
      .then((result) => {
        return result.json();
      })
      .then((json) => {
        this.setState({ list: { items: json, isLoading: false } });
      });
  }

  render() {
    var NavTag = null;
    if (this.state.list.isLoading) {
      NavTag = <NowLoading />;
    } else {
      NavTag = (
        <Nav
          list={this.state.list.items}
          onClick={(id) => {
            var newarticle = Object.assign({}, this.state.article, {
              isLoading: true,
            });
            this.setState({
              article: newarticle,
            });
            fetch(id + '.json')
              .then((result) => {
                return result.json();
              })
              .then((json) => {
                this.setState({
                  article: {
                    item: { title: json.title, desc: json.desc },
                    isLoading: false,
                  },
                });
              });
          }}
        />
      );
    }

    var ArticleTag = null;
    if (this.state.article.isLoading) {
      ArticleTag = <NowLoading />;
    } else {
      ArticleTag = (
        <Article
          title={this.state.article.item.title}
          desc={this.state.article.item.desc}
        />
      );
    }
    return (
      <div className="App">
        <h1>WEB</h1>
        {NavTag}
        {ArticleTag}
      </div>
    );
  }
}

export default App;
