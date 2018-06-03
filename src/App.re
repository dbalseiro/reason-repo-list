let component = ReasonReact.statelessComponent("App");
let make = (_children) => {
  ...component,
  render: (_self) => {
    /* dummy data */
    let dummyRepo: RepoData.repo = {
      stargazer_count: 20,
      full_name: "jsdf/reason-react-hacker-news",
      html_url: "https://github.com/jsdf/reason-react-hacker-news"
    };

    <div className="App">
      <h1>{ReasonReact.stringToElement("Reason Projects")}</h1>
      <RepoItem repo=dummyRepo />
    </div>
  }
};