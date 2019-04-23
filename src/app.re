type route =
  | Home
  | Film
  | FilmDetail(string)
  | NotFound;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Home
  | ["film"] => Film
  | ["film", id ]=> FilmDetail(id)
  | _ => NotFound
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState: () => { route: Home },
  didMount: self => {
    let watchId =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watchId));
  },
  render: self =>
    switch (self.state.route) {
    | Home => <HomePage />
    | Film => <HomePage />
    | FilmDetail(id) => <FilmDetailPage id/>
    | NotFound => <NotFound />
    },
};
