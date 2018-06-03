type state = {repoData: option(RepoData.repo)};

type action =
  | Loaded(RepoData.repo)

let component = ReasonReact.reducerComponent("App");

let dummyRepo: RepoData.repo = {
  stargazer_count: 20,
  full_name: "jsdf/reason-react-hacker-news",
  html_url: "https://github.com/jsdf/reason-react-hacker-news"
};

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
      <button onClick=(_event => self.send(Loaded(dummyRepo)))>
        {ReasonReact.string("Load Repos")}
      </button>;

    let repoItem = switch self.state.repoData {
    | Some(repo) => <RepoItem repo=repo />
    | None       => {loadRepoButton}
    };

    <div className="App">
      <h1>{ReasonReact.string("Reason Projects")}</h1>
      {repoItem}
    </div>
  }
};