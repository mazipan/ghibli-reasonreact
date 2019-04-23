open Utils;

requireCSS("src/FilmPage.css");
let placeholderImage = requireAssetURI("src/placeholder.png");

type state = {
  film: option(Model.film),
  loading: bool,
};

type action =
  | Loaded((Model.film))
  | Loading;

let component = ReasonReact.reducerComponent("FilmDetailPage");

let make = (~id, _children) => {
  ...component,
  initialState: () => {film: None, loading: false},
  reducer: (action, state) =>
    switch (action) {
    | Loading => ReasonReact.Update({...state, loading: true})
    | Loaded((data)) =>
      ReasonReact.Update({
        film: Some(data),
        loading: false,
      });
    },
  didMount: ({send}) => {
    FilmService.fetchData(~remoteUrl=Constants.Url.get_detail_from_id(id), ~decoder=Model.read_film, ~callback=data => send(Loaded(data)))
  },
  render: ({ state }) =>
    <div className="FilmDetailPage">
      (
        switch (state.film) {
          | Some(film) =>
            <div>
              (
                switch (film.image) {
                  | Some(image) => <img alt=film.title src=image className="FilmDetailPage__img"/>
                  | None => <img alt=film.title src=placeholderImage />
                  }
              )
              <h1 className="FilmDetailPage__title">
                <Link href="/film">
                  { ReasonReact.string("" ++ film.title ++ " ("++  film.release_date ++")") }
                </Link>
              </h1>
              <div className="FilmDetailPage__director">
                {ReasonReact.string("Film by " ++ film.director) }
              </div>
              <div className="FilmDetailPage__rating">
                {ReasonReact.string("Rating " ++ film.rt_score) }
              </div>
              <div className="FilmDetailPage__desc">
                {ReasonReact.string(film.description) }
              </div>
            </div>
          | None => ReasonReact.string("loading")
          }
      )
    </div>,
};
