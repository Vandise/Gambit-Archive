export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'MESSAGE',
    payload: data,
  });
};

export default {
  action: 'MESSAGE',
  dispatch,
};