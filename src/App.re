type state = {repoData: option(array(RepoData.repo))};

type action =
  | Loaded(array(RepoData.repo));

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,

  initialState: () => {
    repoData: None
  },

  didMount: (self) => {
    RepoData.fetchRepos()
      |> Js.Promise.then_(repoData => {
          self.send(Loaded(repoData));
          Js.Promise.resolve();
        })
      |> ignore;
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
    let repoItems = switch self.state.repoData {
    | None       => ReasonReact.string("Loading . . .")
    | Some(repos) => ReasonReact.array(
        Array.map(r => <RepoItem repo=r key=r.RepoData.key />, repos)
      )
    };

    <div className="App">
      <h1>{ReasonReact.string("Reason Projects")}</h1>
      {repoItems}
    </div>
  }
};