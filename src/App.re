type state = {repoData: option(array(RepoData.repo))};

type action =
  | Loaded(array(RepoData.repo));

let component = ReasonReact.reducerComponent("App");

let dummyRepos: array(RepoData.repo) = [|
  {
    stargazer_count: 999,
    full_name: "reasonml/reason-tools",
    html_url: "https://github.com/reasonml/reason-tools"
  },
  {
    stargazer_count: 20,
    full_name: "jsdf/reason-react-hacker-news",
    html_url: "https://github.com/jsdf/reason-react-hacker-news"
  }
 |];

let make = (_children) => {
  ...component,
  initialState: () => {
    repoData: None
  },

  reducer: (action, _state) => {
    switch action {
    | Loaded(loadedRepo) => 
      ReasonReact.Update({
        repoData: Some(loadedRepo)
      })
    }
  },
  
  render: (self) => {
    let loadRepoButton =
      <button onClick=(_event => self.send(Loaded(dummyRepos)))>
        {ReasonReact.string("Load Repos")}
      </button>;

    let repoItem = switch self.state.repoData {
    | Some(repo) => ReasonReact.array(Array.map(r => <RepoItem repo=r />, repo))
    | None       => {loadRepoButton}
    };

    <div className="App">
      <h1>{ReasonReact.string("Reason Projects")}</h1>
      {repoItem}
    </div>
  }
};